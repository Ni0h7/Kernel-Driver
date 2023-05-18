# Kernel-Driver-

The driver is a simple Windows kernel mode driver that allows reading and writing to a buffer in kernel space. It provides basic functionality for interacting with a device through the Windows I/O Manager.

Key features include:

Buffer Management: The driver maintains a buffer in kernel space where data can be written to and read from.
Write Operation: It supports write operations where data sent from a user mode application is copied into the kernel buffer.
Read Operation: It also supports read operations where data from the kernel buffer is copied back to the user mode application.
Device Extension: It uses a device extension to store the current state of the device, including the buffer and the current read/write positions.
The user mode application is a simple program that uses the Windows API to communicate with the driver. It opens a handle to the device, sends data to the device using the WriteFile function, and reads data from the device using the ReadFile function. These operations correspond to the write and read operations provided by the driver.

The communication between the user mode application and the driver is handled by the Windows I/O Manager, which forwards I/O requests from the application to the driver and returns the results back to the application.

This project serves as a basic example of how to create a kernel mode driver and a user mode application that interacts with it. It's a good starting point for learning about Windows driver development, but it's not intended for use in a real-world scenario without further development and testing.
