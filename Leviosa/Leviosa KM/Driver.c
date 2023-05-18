#include <ntddk.h>

#define BUFFER_SIZE 256

typedef struct {
    CHAR buffer[BUFFER_SIZE];
    SIZE_T writePosition;
    SIZE_T readPosition;
} DEVICE_EXTENSION, * PDEVICE_EXTENSION;

// Write operation
NTSTATUS Write(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
    PDEVICE_EXTENSION deviceExtension = (PDEVICE_EXTENSION)DeviceObject->DeviceExtension;
    PIO_STACK_LOCATION irpSp = IoGetCurrentIrpStackLocation(Irp);

    // Make sure we don't overflow the buffer
    if (irpSp->Parameters.Write.Length > BUFFER_SIZE - deviceExtension->writePosition) {
        Irp->IoStatus.Status = STATUS_BUFFER_OVERFLOW;
        Irp->IoStatus.Information = 0;
    }
    else {
        // Copy the data from the IRP to the buffer
        RtlCopyMemory(deviceExtension->buffer + deviceExtension->writePosition, Irp->AssociatedIrp.SystemBuffer, irpSp->Parameters.Write.Length);
        deviceExtension->writePosition += irpSp->Parameters.Write.Length;

        Irp->IoStatus.Status = STATUS_SUCCESS;
        Irp->IoStatus.Information = irpSp->Parameters.Write.Length;
    }

    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return Irp->IoStatus.Status;
}

// Read operation
NTSTATUS Read(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
    PDEVICE_EXTENSION deviceExtension = (PDEVICE_EXTENSION)DeviceObject->DeviceExtension;
    PIO_STACK_LOCATION irpSp = IoGetCurrentIrpStackLocation(Irp);

    // Make sure we don't read past the end of the buffer
    if (irpSp->Parameters.Read.Length > deviceExtension->writePosition - deviceExtension->readPosition) {
        Irp->IoStatus.Status = STATUS_END_OF_FILE;
        Irp->IoStatus.Information = 0;
    }
    else {
        // Copy the data from the buffer to the IRP
        RtlCopyMemory(Irp->AssociatedIrp.SystemBuffer, deviceExtension->buffer + deviceExtension->readPosition, irpSp->Parameters.Read.Length);
        deviceExtension->readPosition += irpSp->Parameters.Read.Length;

        Irp->IoStatus.Status = STATUS_SUCCESS;
        Irp->IoStatus.Information = irpSp->Parameters.Read.Length;
    }

    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return Irp->IoStatus.Status;
}

// Driver unload routine
VOID UnloadDriver(PDRIVER_OBJECT DriverObject) {
    // Delete the symbolic link
    UNICODE_STRING symLink;
    RtlInitUnicodeString(&symLink, L"\\??\\BufferDevice");
    IoDeleteSymbolicLink(&symLink);

    // Delete the device
    IoDeleteDevice(DriverObject->DeviceObject);

    DbgPrint("Driver unloaded\n");
}

// Driver entry point
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath); 
    // Create the device
    PDEVICE_OBJECT deviceObject = NULL;
    UNICODE_STRING devName;
    RtlInitUnicodeString(&devName, L"\\Device\\BufferDevice");
    IoCreateDevice(DriverObject, sizeof(DEVICE_EXTENSION), &devName, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &deviceObject);

    // Initialize the device extension
    PDEVICE_EXTENSION deviceExtension = (PDEVICE_EXTENSION)deviceObject->DeviceExtension;
    RtlZeroMemory(deviceExtension, sizeof(DEVICE_EXTENSION));

    // Create the symbolic link
    UNICODE_STRING symLink;
    RtlInitUnicodeString(&symLink, L"\\??\\BufferDevice");
    IoCreateSymbolicLink(&symLink, &devName);

    // Set the driver routines
    DriverObject->DriverUnload = UnloadDriver;
    DriverObject->MajorFunction[IRP_MJ_READ] = Read;
    DriverObject->MajorFunction[IRP_MJ_WRITE] = Write;

    DbgPrint("Driver loaded\n");

    return STATUS_SUCCESS;
}
