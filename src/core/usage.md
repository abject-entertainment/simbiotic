# Simbiotic

## Command Line Usage

`> simbiotic \[options\]`

### Options

- `-c | --config` - Specify a config file from which to load the configuration for the instance.

These options can be used to configure the simulation entirely from the command line, or can be used to override settings in the provided configuration file.

- `-m | --master <simulation-name>[@<resource-path>]` - Create a Master object with the given simulation name. If a resource path is provided, the Master object creates a local pipe for Slave connections at that path.
- `-s | --slave <slave-id>` - Create a Slave object with a given id.
- `-c | --connect [<slave-id>@]<master-location>` - Connects the Slave with the given id to the Master object located at the pipe path or network address provided.  If no Slave id is provided, all slaves will connect to this Master object.