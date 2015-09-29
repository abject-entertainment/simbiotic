# Configuration

This class compiles all the configuration options from the [command line](./usage.md) and the configuration file(s) provided.

## Properties

## Methods

## Configuration File

The configuration file provides instructions for setting up the simulation on this device.  Each device should have its own configuration file.  The [command line](./usage.md) options can override or filter the settings provided by the file.

Additionally, Slave instances can be configured either inline or in their own configuration files (which can make configuring a system much easier).  A slave can be defined as available for run-time load balancing, or provide a list of specific objects to instantiate (or both).  At least one slave in a system should be available for load balancing, so any run-time built objects have a place to live.  If no load balancing Slave is available when a new object needs creation, the Master will create a new, local Slave to receive it (and subsequent objects).

Objects to be created on a slave are specified with an id and their own configuration file.  See the [object docs](./core.md) for specific information about config files for those objects.

### Sample Main Configuration File

``` xml
<simbiotic>
	<master simulation-name="<simulation-name>" pipe-name="/dev/simbiotic" use-lan="true" />
	<slave id="<slave-id>" config="<configuration-file>" />
	<slave id="<slave-id>">
		<controller id="<controller-id>">configuration-file</controller>
	</slave>
	<slave id="<slave-id>" accept-load="true" />
</simbiotic>
```

### Sample Slave Configuration File

``` xml
<slave accept-load="false">
	<actor id="<actor-id>">actor-file</actor>
</slave>
```

### Configuration File Tags

#### `<master>`

- `simulation-name`: A unique name for the simulation this Master object manages.
- `pipe-name`: A name for a local communication pipes, through which local Slave objects connect to this Master object.  If this is not provided, but local Slave objects are created, one Master will have a pipe automatically generated for those Slave objects to connect to.
- `use-lan`: Either "true" or "false", specifies whether this Master object should listen for Slave connections over the network.
- content: no content.

#### `<slave>`

- `config`: A path to a file (local or URL) that specifies the configuration options for this Slave object.  If other parameters are included in this tag, they override any conflicts in the configuration file.
- `id`: An id unique to the simulation system used to identify this Slave instance.
- `accept-load`: Either "true" or "false", specifies whether this Slave object accepts instructions to instantiate run-time-created objects.
- `connect`: Specifies a local pipe path or network address for a Master object that this Slave will connect to.  If not specified, the Slave will automatically connect to the first Master object available.
- content: An optional list of `<controller>` and `<actor>` objects to be instantiated at startup.  Objects will be instantiated in the order they are listed in the configuration.

#### `<controller>`, `<actor>`

- `id`: An id unique to the simulation system used to identify this object.
- content: A file path or URL to a configuration file.



