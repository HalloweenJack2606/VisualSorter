project "VisualSorter"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "On"

    targetdir("../bin/" .. outputdir .. "/%{prj.name}")
    objdir("../bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src",
        "vendor/glfw/include",
        "vendor/glew/include",
        "vendor/glm"
    }

    libdirs
    {
        "vendor/glew/lib"
    }

    links
    {
        "GLFW",
        "opengl32.lib",
        "glew32s.lib"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "LD_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "LD_RELEASE"
        runtime "Release"
        optimize "on"
    
    filter "configurations:Dist"
        defines "LD_DIST"
        runtime "Release"
        optimize "on"