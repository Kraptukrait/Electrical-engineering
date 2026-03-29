# 📘 Project Assignment: Festival Parking System

## 🎯 Scenario

A multi-day music festival (duration: 3 days) requires an efficient parking system for visitors. Two parking areas are available:

* **Parking Area 1:** one entrance and one exit
* **Parking Area 2:** two entrances and two exits

Additionally, there is a central access road where the number of available parking spaces for each parking area should be displayed.

---

## 🧩 Objective

Develop a **technical overall concept** for an intelligent parking system that:

* automates the parking process
* minimizes manual work during the festival
* does not require permanent installations
* allows multi-day parking (including overnight stays)

---

## ⚙️ Requirements

### Functional Requirements

* Display of available parking spaces:

  * per parking area
  * centrally on the access road
* Detection of vehicles at entry and exit
* Real-time management of parking occupancy
* Access control (only authorized vehicles may enter)
* Support for multi-day parking
* Optional: reservation system

### Non-Functional Requirements

* **Mobility:** no permanent installations → everything must be removable (e.g. mobile barriers, cameras)
* **Reliability:** system must run stable during the festival
* **Scalability:** expandable to additional parking areas
* **Usability:** easy to use for visitors

---

## 💡 Tasks

### 1. Concept Development

Develop a complete concept for the parking system:

* How do entry and exit work?
* Which technologies are used?

  * Camera (license plate recognition)
  * Light barriers
  * QR code scanners
* How is unauthorized access prevented?

---

### 2. Payment System

Choose one or more of the following options:

* **Prepayment (online ticket)**
* **On-site payment**
* **Combination**

Answer the following:

* How is payment handled? (e.g. PayPal, card)
* How is payment verified?
* What are the advantages and disadvantages of your solution?

---

### 3. Parking Management

Develop a logic for calculating available spaces:

* Entry → spaces −1
* Exit → spaces +1
* Handling of reservations

Optional:

* Representation as a flowchart (PAP)

---

### 4. System Communication

Plan the communication between system components:

* Use of a protocol such as **MQTT**
* Define:

  * Who sends which data?
  * Which topics are used?
  * Is a central server (MQTT broker) required?

---

### 5. Display System

Design the display system:

* Display on the access road:

  * "Parking Area 1: X available"
  * "Parking Area 2: Y available"
* Displays directly at each parking area

---

### 6. Hardware Planning

Define the required hardware:

* Which devices are needed?

  * Barriers
  * Sensors
  * Cameras
  * Displays
* How is power supplied? (e.g. generator, battery)

---

### 7. Project Organization

Create a project plan including:

* **Kanban Board**

  * Backlog
  * To Do
  * In Progress
  * Review
  * Done
* Task distribution within the team

---

## ❓ Open Questions

* How many parking spaces are available per parking area?
* Is billing based on days or per entry?
* Which payment method will be used?
* What is the exact layout of entrances and exits?

---

## 📦 Deliverables

At the end of the project, you should present:

* Overall concept (documentation)
* Sketches / diagrams (e.g. flowcharts)
* Hardware and software planning
* Optional: a simple prototype or simulation

---

## ⭐ Bonus (optional)

* Simulation of the system (e.g. with software)
* Extension with an app or web interface
* Live dashboard for parking status
