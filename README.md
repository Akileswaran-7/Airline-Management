# Airline Management System

## Project Overview

The Airline Management System is a mini project developed as part of our Data Structures course.  
It is a console-based application designed to manage flight schedules, ticket bookings, and cancellations.  
This project demonstrates the practical use of core data structures such as graphs, binary search trees (BST), linked lists, and arrays to efficiently handle airline data and operations.

The system supports two main user roles:
- **Admins:** Can add airports and flights, and view all flights.
- **Passengers:** Can search for flights, book tickets, cancel bookings, and view ticket details.

The project models real-world airline operations using dynamic memory allocation and provides efficient storage, search, and update functionality for all data.

---

## Key Features

### Airport and Flight Management

- Airports are managed using a graph (implemented with an adjacency list).
- Admins can add new airports and flights.
- Each airport keeps track of its departing flights.
- View all available flights in the system.

### Passenger Management

- Each flight maintains its passenger list using a linked list.
- Passenger details include ID (auto-generated), name, contact information, and seat preference (window or non-window).
- Passengers can be easily added or removed from a flight.

### Booking and Seat Availability

- Seats are managed using a 2D array for each flight.
- The seating chart shows available and booked seats, categorized as window or non-window.
- Passengers can book seats if available, and the chart is updated accordingly.

### Ticket Cancellation

- Passengers can cancel tickets using their unique passenger ID.
- Seat availability is updated dynamically after cancellation.

### Admin and Passenger Roles

- Admins have the ability to add airports, add flights, and view the list of flights.
- Passengers can search for flights, book tickets, cancel bookings, and view their booking details.

---

## Data Structures Used

| Data Structure | Purpose |
|----------------|---------|
| **Binary Search Tree (BST)** | Stores and manages flight records efficiently, allowing fast search, insertion, and deletion of flights by flight number. |
| **Linked List** | Manages the dynamic list of passengers for each flight, making it easy to add or remove passengers. |
| **2D Array** | Represents the seating arrangement of each flight and keeps track of seat occupancy. |
| **Graph (Adjacency List)** | Models the network of airports and the direct flights between them. |

---

## Main Functions

- `InitializeSeats` : Sets up the seat chart for a flight.
- `addAirport` : Adds a new airport to the system.
- `addFlight` : Adds a new flight to a specified airport.
- `addPassenger` : Books a ticket for a passenger and updates the seat chart.
- `cancelPassenger` : Cancels a ticket and frees up the booked seat.
- `displaySeats` : Displays the seating chart of a flight.
- `displayFlights` : Shows all flights available at all airports.
- `displayPassengerTicket` : Displays a passenger’s ticket details.
- `searchFlight` : Searches for a flight by flight number.
- `findAirport` : Finds an airport in the graph by its name.

---

## Conclusion

This project demonstrates how fundamental data structures can be applied to solve real-world problems.  
Graphs are used to represent airport connections, BSTs help manage flight data efficiently, linked lists handle dynamic passenger lists, and arrays keep track of seat availability.  
Together, these structures make the system flexible, dynamic, and easy to maintain.

---

## Team Members

| Name | Roll Number |
|----------------|----------------|
| S. Akieswaran | 2023115037 |
| J. Sathish | 2023115039 |
| Dhivya Dharshini | 2023115023 |

---

## How to Run

To compile and run the project, use the following commands:

```bash
gcc main.c -o airline_system
./airline_system
