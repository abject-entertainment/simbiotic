# Simbiotic
A flexible architecture for hosting distributed simulations.

## Overview
Simbiotic consists of a Master class that organizes all Slave objects and marshals communication and organization between Slaves.  Slave objects organize a set of simulation objects and facilitate communication between them.  Slave objects communicate resources and availability to the Master object to allow for load balancing.

Simbiotic also defines base classes for simulation Actor, Controller and Effect objects.  

### Actor
Actor objects represent all physical entities in the simulation.  

### Effect
Effect objects represent the results of actions taken by Actor objects that may perpetuate independent of the Actor, but do not qualify as Actor objects themselves.  As an example, an exhaust trail, explosion or gravitational effect.

### Controller
Controller objects represent influences in the simulated environment that are universal and not related to physical objects.  These are the 'rules' of the simulation.  As an example, most simulations will include a subclass of PhysicsController to control physical interactions between Actor objects.

### Addressing
All simulation objects, and all properties of those objects, can be referenced using OSC style paths, such as: /actors/{object_id}/position/x.  Properties and objects can be queried, assigned, and subscribed to. These operations are generally considered requests, and may fail if, for example, the object requesting a property assignment does not have permission to do so.  It is up to the receiving object to determine if a request should succeed or fail.  (Eventually, Controller objects will also have authority to determine request permissions.)

### Nesting
Simulations may be nested as well.  This allows for the behavior of an Actor object to be determined by its own simulation.  For example, in a simulation of planets, asteroids and spaceships, a player-controlled spaceship's behavior can be determined by a simulation of its internal workings.

### Configuration
