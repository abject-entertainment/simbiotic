# Path

The Path object represents a resource path in a simulation.  It uniquely identifies an object or property of an object within the simulation, including properties of the simulation itself or its structural components.

A path can be represented as a string in this format: `/path/to/object/property`.  It can also include wildcards, thus `/a/b/*` will match all paths that begin with `/a/b/` and `/a/b/**/c` will match any resource named `c` found on any path that begins with `/a/b/`.

## Constructors

- `Path()` - Creates a Path object representing the resource path `/`.
- `Path(const ::std::string &from_string, bool can_be_segment = false)` - Creates a Path object from a string representation.  Throws an exception if the string does not represent a syntactically correct resource path.  If `can_be_segment` is true, the string does not need to start with `/`.  If it does not, the Path is a segment and cannot be used to identify a resource.  A segment can be combined with another path as a suffix, and can include relative path components (`.` and `..`).
- `Path(const Path &from_prefix, const ::std::string &from_suffix)` - Creates a Path object from an existing Path, concatenated with an additional string.  Throws an exception if the suffix string does not represent a syntactically correct resource path segment.
- `Path(const Path &from_copy)` - Creates a copy of a Path object.
- `Path(const Path &from_prefix, const Path &from_suffix)` - Creates a Path object by concatenating two existing Path objects.

## Properties

- `bool isWildcard() const` - Returns `true` if the path contains any wildcard components.  Otherwise, returns `false`.
- `bool isSegment() const` - Returns `true` if the path is a segment (does not start with '/').
- `bool isRelative() const` - Returns `true` if the path is a segment and includes unresolvable relative components.

## Methods

- `bool matches(const Path &match_other) const` - Returns `true` if this Path object matches the provided parameter.  Otherwise, returns `false`.  If neither Path contain wildcards, then they must match exactly.  In the case of wildcards, the called object is the pattern that should match or 'contain' the parameter.  If both Path objects contain wildcards, the called object must be strictly more general than the parameter, such that the called path matches all possible paths that would match the parameter.
- `bool hasPrefix(const Path &prefix) const` - Returns true if the parameter matches exactly the beginning of the called object's path, including any wildcards.  Wildcards are not evaluated in this case, so `new Path("/a/*/c/d").hasPrefix("/a/b/c");` will return `false`.
- `bool matchPrefix(const Path &prefix) const` - Works like `hasPrefix()`, but evaluates wildcards in the parameter.  Wildcards in this object must match wildcards in the parameter.
- `bool replacePrefix(const Path &old_prefix, const Path &new_prefix)` - If this has the given prefix, that portion of the path is replaced in-place by the given new prefix.
- `bool removePrefix(const Path &prefix)` - If this has the given prefix, that portion of the path is removed in-place.
- `bool appendComponent(const ::std::string &component)` - Adds the given component to the end of this path in-place.
