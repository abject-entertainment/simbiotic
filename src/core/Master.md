# Master

## Overview
The Master class defines the object that organizes the Slave objects running the
simulation.  Slave objects communicate through the Master object.

## Properties

- `const [simbiotic::Router](./Router.md) &router const;` - (READ ONLY) The 
object for routing resource paths to the Slave objects that own them.
- `const bool advertiseOnLAN() const;` - The Master object should advertise the 
simulation over the network.

## Methods

- `Master()
