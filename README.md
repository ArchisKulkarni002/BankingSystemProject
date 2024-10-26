# 🚀 **Banking Management System - Client-Server Architecture** 🏦

## **Overview**  
Hey there! 👋 This is a **Banking Management System** assignment, built from scratch in **C**, using  **Linux system programming** calls. 💪 This project uses **low-level system calls** and **sockets** to set up a slick **client-server architecture**. The client takes input (you know, login and requests), and the server does all the heavy lifting—**verifying, processing, and responding** with results. 

---

## **Features 🛠️**
- **Multi-role Support**:  
  🎭 Four roles (Customer, Employee, Manager, Admin) with their own operations.  
- **Socket Communication**:  
  🔗 Clients connect to the server using **TCP sockets** to send requests and receive responses.  
- **POSIX System Calls**:  
  💻 Mastery over **read, write, send, recv, open, and locking** calls.  
- **Concurrency Control**:  
  🕒 Multiple users? No problem. **File locking** ensures data integrity.  
- **Flat-file Data Storage**:  
  📁 Forget databases—we’re keeping it classic with **files and unique IDs**. 
- **Modular architecture**:  
   Everything is abstracted and seperated into components, and everything is modular!  
- **Role-based Operations**:  
  🎬 Every role gets its own movie:
  - **Customer**: 💸 Manage your money and loans.
  - **Employee**: 👨‍💼 Manage customers and approve loans.
  - **Manager**: 🔑 Keep everyone in check.
  - **Admin**: 🧑‍💻 Rule them all.

---

## **Code Structure 📂**
```
/banking-management-system
├── client.o
├── client_main.c
├── counters
│   ├── admin_counter
│   ├── customer_counter
│   ├── employee_counter
│   ├── feedback_counter
│   ├── loan_counter
│   └── manager_counter
├── headers
│   ├── admin.c
│   ├── admin.h
│   ├── counters.c
│   ├── counters.h
│   ├── customer.c
│   ├── customer.h
│   ├── employee.c
│   ├── employee.h
│   ├── feedback.c
│   ├── feedback.h
│   ├── file_utils.c
│   ├── file_utils.h
│   ├── loans.c
│   ├── loans.h
│   ├── manager.c
│   ├── manager.h
│   ├── menus.c
│   ├── menus.h
│   ├── server.c
│   ├── server.h
│   ├── transactions.c
│   └── transactions.h
├── run
├── runner.c
├── server.o
├── server_main.c
```

---

## **How It Works ⚙️**

### Client-Server Communication 🌐  
- **Client**: Takes user inputs (login, operations) and sends them over to the server via **TCP sockets**. 📲  
- **Server**: Checks user credentials, processes operations, and sends responses back to the client. 💼

**Communication Summary**:  
Client 🛂 ➡️ **(send)** ➡️ Server 🛠️ ➡️ **(process)** ➡️ Client 📥  

### **Persistence with Flat Files** 📄  
Data is stored in **separate files** for each entity (customers, loans, feedback, etc.), with unique **ID-based access** to keep everything organized and consistent. No SQL—just good old **structured text files**. 🔖

---

## **System Calls in Action 🔧**
- **File Handling**:  
  `open()`, `read()`, `write()`, `close()` – because C is all about control!  
- **Sockets**:  
  `socket()`, `bind()`, `listen()`, `accept()`, `send()`, `recv()` – **TCP communication** made simple.  
- **Concurrency**:  
  **File locks** via `fcntl()` – ensuring data integrity even with multiple users.  
- **Error Handling**:  
  **`perror()`** gives detailed error messages so you can debug like a pro. 🕵️‍♂️

---

## **Usage Flow 🛣️**
1. Start the **server** on a specific port.
2. Launch the **client** and log in by selecting a role: **Customer, Employee, Manager, or Admin**.
3. Perform operations (like transferring money, applying for loans, or managing users).
4. **Server processes** the request and sends back the result.
5. Profit! 🤑

---

## **Challenges and Wins 🏆**
- **Concurrency Control**:  
  Implemented **locking mechanisms** to allow simultaneous access while ensuring data integrity.  
- **Socket Communication**:  
  Successfully managed **client-server interaction** using **TCP sockets**.
- **Persistence without a Database**:  
  Stored data in **flat files** with **ID-based management**.  
- **Linux System Calls Expertise**:  
  Got cozy with **low-level POSIX calls** and showed those processes who’s boss. 😎

---

## **What’s Next? 🚀**
- 🔒 **Encryption** for secure communication.  
- 🧵 **Multi-threaded server** for handling more client requests in parallel.  
- 🗄️ **Database integration** (maybe) for larger datasets and faster lookups.  
- 🎨 **GUI client** to make it more user-friendly.  
-  **Tests** to make it more robust.  
-  **Try-catch** like mechanisms to make it fail safe.  

---

## **Conclusion**  
This project is a **showcase of low-level system programming skills** using **C and Linux**, with a strong focus on **client-server communication** and **concurrency control**. By implementing core functionalities like role-based operations and data persistence without databases, it serves as a practical demonstration of how complex systems can be built from scratch using **simple but powerful tools**. 

---

## **License 📝**
Aint no liscense, feel free to use, modify, and distribute this code—just don’t forget to leave a ⭐ on the repo if you like it! 😉

---
*Bad people steal, good people reference!* 😉

\*Generated with GPT and modified with 💖.