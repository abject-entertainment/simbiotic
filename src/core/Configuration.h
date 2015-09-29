// Simbiotic and it's source files are (c) 2015, Abject Entertainment
#include <boost/property_tree/ptree_fwd.hpp>

namespace simbiotic
{
	class ObjectConfiguration
	{
	public:
		ObjectConfiguration(int config_version, ::boost::property_tree::wptree &config_data);

		const ::std::wstring &getObjectName() const;
		const ::std::string &getObjectClass() const;
		const ::boost::property_tree::wptree &getInitProperties() const;

	private:
		::std::wstring _obj_name;
		::std::string _obj_class;
		::boost::property_tree::wptree &_init_props;
	};

	class MasterConfiguration
	{
	public:
		MasterConfiguration(int config_version, ::boost::property_tree::wptree &config_data);

		const ::std::wstring &simulationName() const;
		const ::std::wstring &simulationDescription() const;

		const bool isLANEnabled() const;
		const bool allowsPipes() const;

	private:
		::std::wstring _sim_name;
		::std::wstring _sim_desc;
	};

	class SlaveConfiguration
	{
	public:
		SlaveConfiguration(int config_version, ::boost::property_tree::wptree &config_data);

		const ::std::array<ObjectConfiguration*> &startupObjects() const;

	private:
		::std::array<ObjectConfiguration*> _startup_objects;
	};

	class Configuration
	{
	public:
		Configuration(::boost::property_tree::wptree &config_data);

		const bool masterIsLocal() const;
		const bool hasLocalSlave() const;

		const MasterConfiguration *masterConfig() const;
		const SlaveConfiguration *slaveConfig() const;

	private:
		bool _master;
		bool _slave;
	};
}