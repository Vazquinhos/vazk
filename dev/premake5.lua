workspace "vazk"
   language "C++"
   configurations { "Debug", "Release" }
   platforms { "x64" }
   location "vs"
   buildoptions '/std:c++latest'
   systemversion "10.0.15063.0"
   
   targetdir "$(SolutionDir)bin/%{cfg.buildcfg}"
   debugdir "../data"
   
   filter "configurations:Debug"
      defines { "DEBUG" }
	  rtti ("off")
	  characterset ("MBCS")
	  symbols "on"

   filter "configurations:Release"
      defines { "NO_DEBUG" }
	  rtti ("off")
      optimize "On"

group "app"
project "vazkapp"
	kind "ConsoleApp"
	
	warnings "Extra" 
	
	files { "../**.cpp" }

	includedirs
	{
		"../vazk/",
	}
	
	libdirs
	{
		"$(SolutionDir)lib/%{cfg.buildcfg}",
	}
	
	links
	{
		"vazk"
	}

group "library"
project "vazk"
	kind "StaticLib"
	files {"../vazk/**.hpp", "../vazk/**.cpp"}