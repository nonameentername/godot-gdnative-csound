all:
	scons platform=linux bits=64

.PHONY: godot-cpp

godot-cpp:
	(cd godot-cpp && scons platform=linux bits=64 generate_bindings=yes)

