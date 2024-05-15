workspace "VisualSorter"
    architecture "x64"
    startproject "VisualSorter"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    flags
    {
        "MultiProcessorCompile"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "VisualSorter/vendor/glfw"
group ""

include "VisualSorter"