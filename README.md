# AVENGERS-BATTLE-SIMULATION
A C++ mini project using OOP to manage dynamic Quantum Suit upgrades and combat between Avengers and enemies.

Project Title: Avengers’ Quantum Suit Upgrade Simulation

Objective:
  To design and implement a Quantum Suit Management System for the Avengers using Object-Oriented Programming (OOP) principles such as polymorphism, operator overloading, and    function overloading. The system simulates a real-time battle between Avengers and enemies while managing dynamic upgrades, suit conditions, and battle events.

Background:
  The Avengers, preparing for an intergalactic battle, are equipped with Quantum Nanotech Suits (QNS) developed by Tony Stark. These suits adapt dynamically on the battlefield   by:
    
    Absorbing energy to increase power.
    Reinforcing durability.
    Overclocking for high-damage attacks.
    However, excessive usage leads to overheating, which can disable the suits.
    Effective management of these suits is crucial to ensure victory.

Key Components:
1. QNS (Quantum Nanotech Suit) Class:

Represents an adaptive combat suit.

    Attributes: 
            powerLevel
            durability
            energyStorage
            heatLevel.
    Supports:
            Operator Overloading for battle actions (e.g., +, -, *, /).
            Function Overloading for suit enhancements.
            Comparison Operators for evaluating suit strength.
            Built-in safety constraints for overheating and destruction.

2. Avenger Class

   Represents a hero with a QNS.
        
        Attributes: 
                  name
                  attackStrength
                  QNS instance.
        
        Supports:
                  Attacking another Avenger.
                  Repairing or boosting suits.
                  Upgrading from extra suits.
                  Displays current suit status.
        
        Constraints ensure only operational Avengers participate in the battle.

3. Battle Class

Manages the simulation of the battle.
    
    Attributes: 
              lists of heroes
              enemies
              battleLog.
              
    Supports:
            Starting and managing battle rounds.
            Logging significant battle events.
            Evaluating battle outcomes (heroes win, enemies win, or tie).
    
    System Features:
            Real-Time Simulation: Dynamic suit behavior during battles.
            Battle Logging: Records key events like attacks, repairs, boosts, and upgrades.
            Command-Driven Control: Battle progresses through structured commands like Attack, Repair, Upgrade, PrintBattleLog, etc.
            Resource Management: Tracks suit usage and prevents overuse through defined limits.

Input Format:
          
    Initialization of suits, heroes, and enemies.
            Series of commands (e.g., battle start, attacks, boosts).
            Status and result queries.
          
    Sample Functionality:
            Attack: Avenger damages another’s suit based on attack strength.
            Boost: Temporarily increase power with overheating risk.
            Repair: Reduce heat and restore durability.
            Upgrade: Use spare suits to enhance current ones.

Constraints:

        Suits shut down if heatLevel > 500.
        Suits are destroyed if durability ≤ 0.
        powerLevel capped at 5000.
        First-come-first-serve suit assignment.

Outcome:

A structured and extensible simulation that demonstrates the application of advanced OOP concepts in a creative and interactive setting. The project promotes strategic thinking and careful resource management through realistic battle dynamics and constraints.

[Avengers’ Quantum Suit Upgrade.pdf](https://github.com/user-attachments/files/20345318/Avengers.Quantum.Suit.Upgrade.pdf)


