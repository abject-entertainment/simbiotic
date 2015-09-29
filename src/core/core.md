# Simbiotic

- [Command-Line Usage](./usage.md)

# Core Classes

- [Configuration](./Configuration.md): A class representing the configuration
being loaded.
- [Master](./Master.md): The simulation master object that manages communication
between slaves.
- [Slave](./Slave.md): The simulation worker object that manages the sim objects
and communcates through the master.
- [Actor](./Actor.md): The physical objects interacting in the simualation.
- [Controller](./Controller.md): Non-physical objects that interact with and
control the actions of other objects.
- [Effect](./Effect.md): Transient effects produced by Actor and Controller
objects that interact in the simulation more or less independently of their
creator objects.

# Utility Classes

- [Path](./Path.md): A utility class representing a resource path in the
simulation, including helpful methods for manipulating and handling them.
- [Router](./Router.md): A utility class owned by the Master object for routing
resource paths to specific slave objects.
- [CommunicationManager](./CommunicationManager.md): A utility class used by
the Master and Slave objects for passing messages back and forth.