#include "mmm_common.h"
#include <Windows.h>
#include <optional>

namespace mmm
{
	namespace common
	{
		Storage::Storage( )
			: error( false ), 
			  updateTime( 0 ),
			  mainLuaVM( 0 )
		{

		}

		Storage& Storage::instance( )
		{
			static Storage inst;
			return inst;
		}

		namespace
		{
			std::optional<bool> fleetops;
			std::optional<Version> loaded_fleetops_version;
		}

		bool fleetops_present() noexcept
		{
			if (!fleetops.has_value())
			{
				HMODULE mod = GetModuleHandle(L"FleetOpsHook.dll");
				fleetops = mod != INVALID_HANDLE_VALUE;
				if (fleetops.value())
				{
					wchar_t path[MAX_PATH + 1];
					memset(&path[0], 0, sizeof(path));
					if (0 != GetModuleFileName(mod, &path[0], MAX_PATH))
					{
						const DWORD size = GetFileVersionInfoSize(path, nullptr);

						std::vector<char> version_info_data(size, 0);

						GetFileVersionInfo(path, 0, size, &version_info_data[0]);

						VS_FIXEDFILEINFO* version_info;
						uint32_t version_info_size = sizeof(VS_FIXEDFILEINFO);
						VerQueryValue(&version_info_data[0], L"\\", reinterpret_cast<LPVOID*>(&version_info), &version_info_size);

						Version version;
						version.major = (version_info->dwFileVersionMS & 0xffff0000) >> 16;
						version.minor = version_info->dwFileVersionMS & 0xffff;
						version.patch = (version_info->dwFileVersionLS & 0xffff0000) >> 16;
						version.revision = version_info->dwFileVersionLS & 0xffff;
						loaded_fleetops_version = version;
					}
				}
			}
			return fleetops.value();
		}

		Version fleetops_version() noexcept
		{
			if (fleetops_present() && loaded_fleetops_version.has_value())
			{
				return loaded_fleetops_version.value();
			}
			return {};
		}
	}
}
