// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#pragma once

namespace ZoneTool
{
	namespace std_z
	{
		typedef char int8_t;
		typedef unsigned char uint8_t;
		typedef short int16_t;
		typedef unsigned short uint16_t;
		typedef int int32_t;
		typedef unsigned int uint32_t;
		typedef long long int64_t;
		typedef unsigned long long uint64_t;
		typedef unsigned long long uintptr_t;
	}

	struct dumpListEntry
	{
		void* __ptr64 start;
		int entry_count;
		int entry_size;
	};

	enum DUMP_TYPE
	{
		DUMP_TYPE_INT = 0,
		DUMP_TYPE_STRING = 1,
		DUMP_TYPE_ASSET = 2,
		DUMP_TYPE_ARRAY = 3,
		DUMP_TYPE_OFFSET = 4,
		DUMP_TYPE_FLOAT = 5,
		DUMP_TYPE_RAW = 6,
		DUMP_TYPE_LONGLONG = 7,
	};

	const char DUMP_EXISTING = 1;
	const char DUMP_NONEXISTING = 0;

	class AssetDumper
	{
	protected:
		std::vector<dumpListEntry> list;
		FILE* fp = nullptr;

		template <typename T>
		void write_internal(const T& value)
		{
			if (fp)
			{
				fwrite(&value, sizeof(T), 1, fp);
			}
		}

		template <typename T>
		void write_internal(const T& value, DUMP_TYPE type)
		{
			if (fp)
			{
				fwrite(&type, 1, 1, fp);
				fwrite(&value, sizeof(T), 1, fp);
			}
		}

		void write_string_internal(const char* str)
		{
			if (fp)
			{
				fwrite(str, strlen(str) + 1, 1, fp);
			}
		}

	public:
		AssetDumper()
		{
			list.clear();
		}

		~AssetDumper()
		{
			// close file pointer
			close();
		}

		bool open(const std::string& filename)
		{
			close();
			fp = FileSystem::FileOpen(filename, "wb");
			return fp != nullptr;
		}

		void close()
		{
			list.clear();
			FileSystem::FileClose(fp);
		}

		void dump_float(float f)
		{
			write_internal(f, DUMP_TYPE_FLOAT);
		}

		void dump_int(std_z::int32_t i)
		{
			write_internal(i, DUMP_TYPE_INT);
		}

		void dump_uint(std_z::uint32_t i)
		{
			write_internal(i, DUMP_TYPE_INT);
		}

		void dump_longlong(std_z::int64_t l)
		{
			write_internal(l, DUMP_TYPE_LONGLONG);
		}

		void dump_ulonglong(std_z::uint64_t l)
		{
			write_internal(l, DUMP_TYPE_LONGLONG);
		}

		void dump_string(char* s)
		{
			if (fp)
			{
				if (s)
				{
					auto list_index = 0;
					for (auto old_entry : list)
					{
						if (old_entry.start == s && old_entry.entry_size == 1 && old_entry.entry_count == 1)
						{
							this->write_internal<std_z::int32_t>(list_index, DUMP_TYPE_OFFSET);
							this->write_internal<std_z::uintptr_t>(0);
							return;
						}
						list_index++;
					}

					dumpListEntry entry;
					entry.entry_count = 1;
					entry.entry_size = 1;
					entry.start = reinterpret_cast<void* __ptr64>(s);
					list.push_back(entry);

					this->write_internal<char>(DUMP_EXISTING, DUMP_TYPE_STRING);
					this->write_string_internal(s);
				}
				else
				{
					this->write_internal<char>(DUMP_NONEXISTING, DUMP_TYPE_STRING);
				}
			}
		}

		void dump_string(const char* s)
		{
			this->dump_string(const_cast<char*>(s));
		}

		template <typename T>
		void dump_asset(T* asset)
		{
			if (fp)
			{
				if (asset && asset->name)
				{
					auto list_index = 0;
					for (auto old_entry : list)
					{
						if (reinterpret_cast<std_z::uintptr_t>(old_entry.start) <= std_z::uintptr_t(asset) &&
							reinterpret_cast<std_z::uintptr_t>(old_entry.start) + (old_entry.entry_count ? old_entry.entry_count - 1 : 0) * old_entry.
							entry_size >= std_z::uintptr_t(asset) &&
							(std_z::uintptr_t(asset) - reinterpret_cast<std_z::uintptr_t>(old_entry.start)) % old_entry.entry_size == 0)
						{
							this->write_internal<std_z::int32_t>(list_index, DUMP_TYPE_OFFSET);
							this->write_internal<std_z::uintptr_t>((std_z::uintptr_t(asset) - reinterpret_cast<std_z::uintptr_t>(old_entry.start)) / old_entry.entry_size);
							return;
						}
						list_index++;
					}

					dumpListEntry entry;
					entry.entry_count = 1;
					entry.entry_size = sizeof(T);
					entry.start = static_cast<void* __ptr64>(asset);
					list.push_back(entry);

					this->write_internal<char>(DUMP_EXISTING, DUMP_TYPE_ASSET);
					this->write_string_internal(asset->name);
				}
				else
				{
					this->write_internal<char>(DUMP_NONEXISTING, DUMP_TYPE_ASSET);
				}
			}
		}

		template <typename T> void dump_array(T* data, int array_size)
		{
			if (fp)
			{
				if (data && array_size > 0)
				{
					int list_index = 0;
					for (auto old_entry : list)
					{
						if (sizeof(T) == old_entry.entry_size &&
							// Filter out the structs it definitely can't be without having to actually save what struct it is
							reinterpret_cast<std_z::uintptr_t>(old_entry.start) <= std_z::uintptr_t(data) && // Check if it is in the range of the current array
							reinterpret_cast<std_z::uintptr_t>(old_entry.start) + (old_entry.entry_count ? old_entry.entry_count - 1 : 0) * old_entry.
							entry_size >= std_z::uintptr_t(data) && // ^
							(std_z::uintptr_t(data) - reinterpret_cast<std_z::uintptr_t>(old_entry.start)) % old_entry.entry_size == 0)
							// Check if the data is actually at the start of an array entry
						{
							this->write_internal<std_z::int32_t>(list_index, DUMP_TYPE_OFFSET);
							this->write_internal<std_z::uintptr_t>((std_z::uintptr_t(data) - reinterpret_cast<std_z::uintptr_t>(old_entry.start)) / old_entry.entry_size);
							return;
						}
						list_index++;
					}

					dumpListEntry entry;
					entry.entry_count = array_size;
					entry.entry_size = sizeof(T);
					entry.start = static_cast<void* __ptr64>(data);
					list.push_back(entry);

					this->write_internal<std_z::uint32_t>(array_size, DUMP_TYPE_ARRAY);
					fwrite(data, sizeof(T), array_size, fp);
				}
				else
				{
					this->write_internal<std_z::uint32_t>(0, DUMP_TYPE_ARRAY);
				}
			}
		}

		template <typename T> void dump_single(T* asset)
		{
			return this->dump_array<T>(asset, 1);
		}

		template <typename T> void dump_raw(T* data, int size)
		{
			if (fp)
			{
				if (data && size > 0)
				{
					int list_index = 0;
					for (auto old_entry : list)
					{
						if (sizeof(T) == old_entry.entry_size &&
							// Filter out the structs it definitely can't be without having to actually save what struct it is
							reinterpret_cast<std_z::uintptr_t>(old_entry.start) <= std_z::uintptr_t(data) && // Check if it is in the range of the current array
							reinterpret_cast<std_z::uintptr_t>(old_entry.start) + (old_entry.entry_count ? old_entry.entry_count - 1 : 0) * old_entry.
							entry_size >= std_z::uintptr_t(data) && // ^
							(std_z::uintptr_t(data) - reinterpret_cast<std_z::uintptr_t>(old_entry.start)) % old_entry.entry_size == 0)
							// Check if the data is actually at the start of an array entry
						{
							this->write_internal<std_z::int32_t>(list_index, DUMP_TYPE_OFFSET);
							this->write_internal<std_z::uintptr_t>((std_z::uintptr_t(data) - reinterpret_cast<std_z::uintptr_t>(old_entry.start)) / old_entry.entry_size);
							return;
						}
						list_index++;
					}

					dumpListEntry entry;
					entry.entry_count = 1;
					entry.entry_size = size;
					entry.start = static_cast<void* __ptr64>(data);
					list.push_back(entry);

					this->write_internal<std_z::uint32_t>(size, DUMP_TYPE_RAW);
					fwrite(data, size, 1, fp);
				}
				else
				{
					this->write_internal<std_z::uint32_t>(0, DUMP_TYPE_RAW);
				}
			}
		}
	};
}
