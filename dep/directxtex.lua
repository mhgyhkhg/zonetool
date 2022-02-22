directxtex = {}

function directxtex:include()
	includedirs {
		path.join(DependencyFolder(), "DirectXTex/DirectXTex")
	}
end

function directxtex:link()
	self:include()
	links {
		"directxtex"
	}
end

function directxtex:project()
	local folder = DependencyFolder();

	project "directxtex"
	
		location "%{wks.location}/dep"
		kind "StaticLib"
		language "C++"
		
		files { 
			path.join(folder, "DirectXTex/DirectXTex/*.h"),
			path.join(folder, "DirectXTex/DirectXTex/*.cpp"),
			path.join(folder, "DirectXTex/DirectXTex/*.inl"),
		}

		removefiles {
			path.join(folder, "DirectXTex/DirectXTex/BCDirectCompute.cpp"),
			path.join(folder, "DirectXTex/DirectXTex/BCDirectCompute.h"),
		}
		
		self:include()

		-- Disable warnings. They do not have any value to us since it is not our code.
		warnings "off"
end
