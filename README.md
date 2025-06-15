📌 Expedia-Style Travel Reservation Backend (C++)

A modular C++ backend system simulating a travel booking platform similar to Expedia. The system handles flights, hotels, itineraries, and payment processing using extensible, mock service managers. This project showcases solid Object-Oriented Programming (OOP) practices, clean software architecture, and the use of several foundational design patterns.
📖 Features

    ✅ Modular service managers for handling flights and hotel reservations.

    ✅ Factory Pattern used to dynamically retrieve service managers based on providers.

    ✅ Composite Pattern implementation for managing single and grouped reservations through an ItineraryReservation class.

    ✅ Simulated external API integrations for multiple airlines and hotel providers.

    ✅ Basic payment system simulation with polymorphic card types (Credit/Debit).

    ✅ Menu-driven command-line interface for customers and system administrators.

    ✅ File-based data persistence used to simulate lightweight backend storage.

    ✅ Applied Singleton Pattern for menu systems and system controllers in this academic prototype.

    ✅ Structured around Clean Architecture principles with separation of concerns and SOLID-compliant OOP design.

🛠️ Technologies & Concepts

    C++17

    Object-Oriented Programming (OOP)

    Design Patterns: Factory, Composite, Singleton

    File I/O for Data Persistence

    Command-line Interface

    Clean Architecture Concepts
📈 Future Improvements

    Replace file-based persistence with a relational database (SQLite or PostgreSQL).

    Refactor Singletons into dependency-injected services for better testability and scalability.

    Expand API integrations for additional service providers (e.g. car rentals, cruises).
