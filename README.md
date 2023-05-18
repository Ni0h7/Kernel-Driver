<br />
<div align="center">
  <a href="https://github.com/Ni0h7/Kernel-Driver-">
    <img src="Logo/Logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Best-README-Template</h3>

  <p align="center">
    An awesome README template to jumpstart your projects!
    <br />
    <a href="https://github.com/othneildrew/Best-README-Template"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/othneildrew/Best-README-Template">View Demo</a>
    ·
    <a href="https://github.com/othneildrew/Best-README-Template/issues">Report Bug</a>
    ·
    <a href="https://github.com/othneildrew/Best-README-Template/issues">Request Feature</a>
  </p>
</div>

This is one of my first attempts into making a kernel driver using buffer management and reading & writing.
Communication: Interacting with a device through the Windows I/O Manager.

Key features include:

Buffer Management: The driver maintains a buffer in kernel space where data can be written to and read from.
Write Operation: It supports write operations where data sent from a user mode application is copied into the kernel buffer.
Read Operation: It also supports read operations where data from the kernel buffer is copied back to the user mode application.
Device Extension: It uses a device extension to store the current state of the device, including the buffer and the current read/write positions.
The user mode application is a simple program that uses the Windows API to communicate with the driver. It opens a handle to the device, sends data to the device using the WriteFile function, and reads data from the device using the ReadFile function. These operations correspond to the write and read operations provided by the driver.

The communication between the user mode application and the driver is handled by the Windows I/O Manager, which forwards I/O requests from the application to the driver and returns the results back to the application.

This project serves as a basic example of how to create a kernel mode driver and a user mode application that interacts with it. It's a good starting point for learning about Windows driver development, but it's not intended for use in a real-world scenario without further development and testing.
