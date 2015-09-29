
#pragma once

#include <string>
#include <vector>

namespace simbiotic
{
	typedef ::std::vector< ::std::string >::iterator PathIterator;
	typedef ::std::vector< ::std::string >::const_iterator constPathIterator;

	class Path
	{
	public:
		Path();
		Path(const ::std::string &from_string);
		Path(const Path &from_copy);
		Path(const Path &from_prefix, const Path &from_suffix);
		Path(const Path &from_prefix, const ::std::string &from_suffix);
		Path(const ::std::string &from_prefix, const ::std::string &from_suffix);
		Path(const ::std::string &from_prefix, const Path &from_suffix);

		bool isWildcard() const;
		inline bool isSegment() const { return _is_segment; }
		bool matches(const Path &pattern) const;
		bool hasPrefix(const Path &prefix) const;
		bool matchesPrefix(const Path &prefix_pattern) const;

		bool replacePrefix(const Path &old_prefix, const Path &new_prefix);
		bool removePrefix(const Path &prefix);
		bool appendComponent(const ::std::string &component);

		constPathIterator begin() const;
		constPathIterator end() const;
		PathIterator begin();
		PathIterator end();
		::std::string::size_type size() const;

		::std::string toString() const;

	protected:
		bool _is_segment;
		::std::vector< ::std::string > _components;

		bool _match(const Path &pattern, bool allow_tail = false, bool allow_pattern_tail = false) const;
	};
}