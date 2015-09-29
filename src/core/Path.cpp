
#include "Path.h"
#include <sstream>
#include <iterator>
#include <stdexcept>
#include <iostream>


namespace simbiotic
{
	Path::Path() 
	: _is_segment(false)
	, _components() {}

	Path::Path(const ::std::string &from_string)
	: Path()
	{
		bool can_be_segment = true;
		size_t start = 0;

		if (from_string[0] == '/')
			{ start = 1; }
		else if (can_be_segment)
			{ _is_segment = true; }
		else
			{ throw ::std::invalid_argument("from_string must begin with '/'."); }

		while (start < from_string.length())
		{
			size_t end = from_string.find('/', start);
			if (end == ::std::string::npos)
				{ end = from_string.length(); }

			if (end > start)
			{
				::std::string component = from_string.substr(start, end-start);
				if (component == ".")
					{ /* skip */ }
				else if (component == "..")
				{ 
					if (_components.size() > 0)
						{ _components.pop_back(); }
					else if (can_be_segment)
					{
						_is_segment = true;
						_components.push_back(component);
					}
				}
				else
					{ _components.push_back(component); }
			}

			start = end + 1;
		}
	}

	Path::Path(const Path &from_prefix, const ::std::string &from_suffix)
	: Path(from_prefix, Path(from_suffix)) {}

	Path::Path(const ::std::string &from_prefix, const ::std::string &from_suffix)
	: Path(Path(from_prefix), Path(from_suffix)) {}

	Path::Path(const ::std::string &from_prefix, const Path &from_suffix)
	: Path(Path(from_prefix), from_suffix) {}

	Path::Path(const Path &from_copy) 
	: _is_segment(from_copy._is_segment)
	, _components(from_copy._components)
	{}

	Path::Path(const Path &from_prefix, const Path &from_suffix)
	: _is_segment(from_prefix._is_segment)
	, _components(from_prefix._components)
	{
		//::std::cout << "\nCONCAT CONSTRUCT: " << from_prefix.toString() << " " << from_suffix.toString();
		for (constPathIterator it = from_suffix.begin(); it != from_suffix.end(); ++it)
		{
			//::std::cout << "APPENDING: " << *it << "\n";
			if (it->compare("..") == 0)
			{
				if (_components.size() > 0)
					{ _components.pop_back(); }
				else if (_is_segment)
					{ _components.push_back(*it); }
				else
				{
					throw ::std::invalid_argument("Path segment \"" + from_suffix.toString() + 
						"\" cannot be appended to path \"" + from_prefix.toString() + "\".");
				}
			}
			else if (it->compare(".") == 0)
				{ /* skip */ }
			else
				{ _components.push_back(*it); }
		}
	}

	bool Path::isWildcard() const
	{
		for (constPathIterator it = begin(); it != end(); ++it)
		{
			if ((it->compare("*") == 0) || (it->compare("**") == 0))
				{ return true; }
		}
		return false;
	}

	bool Path::matches(const Path &pattern) const
	{ return _match(pattern, false); }
	bool Path::matchesPrefix(const Path &prefix) const
	{ return _match(prefix, true); }

#define log(x) 
	//::std::cout <<
	bool Path::_match(const Path &pattern, bool allow_tail, bool allow_pattern_tail) const
	{
		constPathIterator it1 = begin();
		constPathIterator it2 = pattern.begin();

		bool wildcard = false; // processing a '**' wildcard

		while (it1 != end() && it2 != pattern.end())
		{
			if (wildcard)
			{
				if (it2->compare(*it1) == 0)
				{ // matches the next bit, so continue as normal
					log(" . " << *it2 << " matches " << *it1 << ", exiting wildcard.\n");
					wildcard = false;
					++it1; ++it2;
				}
				else
				{ // consume next component as part of the wildcard match
					log(" . " << *it1 << " consumed by **.\n");
					++it1;
				}
			}
			else if (it2->compare("**") == 0)
			{
				log("Found **, begin wildcard matching.\n");
				wildcard = true;
				++it2;
			}
			else
			{
				if (it1->compare(*it2) == 0)
				{ /* keep going */ 
					log(*it1 << " matches " << *it2 << ", continuing.\n");
				}
				else if ((it2->compare("*") == 0) && (it2->compare("**") != 0))
				{ /* keep going */ 
					log(*it1 << " matches " << *it2 << ", continuing.\n");
				}
				else
				{
					log(*it1 << " DOES NOT MATCH " << *it2 << ", failing.\n");
					return false;
				}

				++it1; ++it2;
			}
		}

		if (it1 != end() && !allow_tail)
		{
			if (!wildcard)
			{
				log("Unmatched suffix, failing.\n");
				return false;
			}
		}
		else if (it2 != pattern.end() && !allow_pattern_tail)
		{
			log("Pattern unmatched, failing.\n");
			return false;
		}

		return true;
	}
#undef log

	bool Path::hasPrefix(const Path &prefix) const
	{
		if (prefix.size() <= size())
		{
			constPathIterator it1 = begin();
			constPathIterator it2 = prefix.begin();
			while (it2 != prefix.end())
			{
				if (*it1 != *it2)
					{ return false; }
				++it1;
				++it2;
			}

			return true;
		}
		return false;
	}

	bool Path::replacePrefix(const Path &old_prefix, const Path &new_prefix)
	{
		if (hasPrefix(old_prefix))
		{
			removePrefix(old_prefix);
			_components.insert(_components.begin(), new_prefix.begin(), new_prefix.end());
			return true;
		}
		return false;
	}

	bool Path::removePrefix(const Path &prefix)
	{
		if (hasPrefix(prefix))
		{
			_components.erase(_components.begin(), _components.begin() + prefix.size());
			return true;
		}
		return false;
	}

	bool Path::appendComponent(const ::std::string &component)
	{
		if (component.find('/') != ::std::string::npos)
			{ throw ::std::invalid_argument("appendComponent() only adds a single path component (cannot contain '/')."); }
		else if (component == "..")
		{
			if (_components.size() > 0)
				{ _components.pop_back(); }
			else if (_is_segment)
				{ _components.push_back(component); }
			else
				{ return false; } //throw ::std::invalid_argument("Cannot append '..' to '/'."); }
		}
		else if (component == ".")
			{ /* skip */ }
		else
			{ _components.push_back(component); }

		return true;
	}

	PathIterator Path::begin()
	{ return _components.begin(); }
	PathIterator Path::end()
	{ return _components.end(); }
	constPathIterator Path::begin() const
	{ return _components.begin(); }
	constPathIterator Path::end() const
	{ return _components.end(); }
	
	::std::string::size_type Path::size() const
	{ return _components.size(); }

	::std::string Path::toString() const
	{
		if (size() == 0 && !isSegment())
			{ return "/"; }
		else
		{
			::std::stringstream output;
			for (constPathIterator it = begin(); it != end(); ++it)
			{ output << "/" << *it; }
			return output.str();
		}
	}

}