#pragma once
#include "filesystem.hpp"

namespace zonetool
{
	namespace assetmanager
	{
		struct dump_entry
		{
			std::uintptr_t ptr;
		};

		enum dump_type : std::uint8_t
		{
			DUMP_TYPE_ERROR = 0,
			DUMP_TYPE_CHAR = 1,
			DUMP_TYPE_SHORT = 2,
			DUMP_TYPE_INT = 3,
			DUMP_TYPE_FLOAT = 4,
			DUMP_TYPE_INT64 = 5,
			DUMP_TYPE_STRING = 6,
			DUMP_TYPE_ASSET = 7,
			DUMP_TYPE_ARRAY = 8,
			DUMP_TYPE_OFFSET = 9,
			DUMP_TYPE_RAW = 10,
			DUMP_TYPE_COUNT = 11,
		};

		const std::uint8_t DUMP_EXISTING = 1;
		const std::uint8_t DUMP_NONEXISTING = 0;

		class dumper
		{
		private:
			filesystem::file file;
			std::vector<dump_entry> dump_entries;

			bool is_entry_dumped(std::uintptr_t ptr)
			{
				for (std::size_t i = 0; i < dump_entries.size(); i++)
				{
					if (dump_entries[i].ptr == ptr)
					{
						return true;
					}
				}
				return false;
			}

			std::int32_t get_entry_dumped_index(std::uintptr_t ptr)
			{
				for (std::size_t i = 0; i < dump_entries.size(); i++)
				{
					if (dump_entries[i].ptr == ptr)
					{
						return static_cast<std::int32_t>(i);
					}
				}
				return static_cast<std::int32_t>(-1);
			}

			void add_entry_dumped(std::uintptr_t str)
			{
				dump_entry entry;
				entry.ptr = str;
				dump_entries.push_back(entry);
			}

			void write_type(dump_type type)
			{
				file.write(&type);
			}

			void write_existing(std::uint8_t existing)
			{
				file.write(&existing);
			}

			void write_char_internal(std::int8_t c)
			{
				write_type(DUMP_TYPE_CHAR);
				file.write(&c);
			}

			void write_short_internal(std::int16_t s)
			{
				write_type(DUMP_TYPE_SHORT);
				file.write(&s);
			}

			void write_int_internal(std::int32_t s)
			{
				write_type(DUMP_TYPE_INT);
				file.write(&s);
			}

			void write_float_internal(float f)
			{
				write_type(DUMP_TYPE_FLOAT);
				file.write(&f);
			}

			void write_int64_internal(std::int64_t i64)
			{
				write_type(DUMP_TYPE_INT64);
				file.write(&i64);
			}

			void write_string_internal(const char* str)
			{
				file.write_string(str);
			}

			template <typename T>
			void write_internal(const T* data, std::size_t size = sizeof(T), std::size_t count = 1)
			{
				file.write(data, size, count);
			}

			template <typename T>
			void write_array_internal(const T* value, std::uint32_t array_size)
			{
				file.write(value, sizeof(T), array_size);
			}

		public:
			dumper(const std::string& name)
			{
				initialize(name);
			}

			dumper()
			{

			}

			~dumper()
			{
				file.close();
				dump_entries.clear();
			}

			void initialize(const std::string& name)
			{
				file = filesystem::file(name);
				file.open("wb");

				dump_entries.clear();
			}

			bool is_open()
			{
				return file.get_fp() != nullptr;
			}

			auto open()
			{
				if (!is_open())
				{
					file.open("wb");
				}
				return is_open();
			}

			auto open(const std::string& name)
			{
				if (!is_open())
				{
					initialize(name);
				}
				return is_open();
			}

			auto close()
			{
				file.close();
			}

			void dump_char(std::int8_t c)
			{
				write_char_internal(c);
			}

			void dump_short(std::int16_t s)
			{
				write_short_internal(s);
			}

			void dump_int(std::int32_t i)
			{
				write_int_internal(i);
			}

			void dump_float(float f)
			{
				write_float_internal(f);
			}

			void dump_int64(std::int64_t i)
			{
				write_int64_internal(i);
			}

			void dump_string(char* str)
			{
				if (str)
				{
					if (is_entry_dumped(reinterpret_cast<std::uintptr_t>(str)))
					{
						write_type(DUMP_TYPE_OFFSET);
						std::uint32_t index = get_entry_dumped_index(reinterpret_cast<std::uintptr_t>(str));
						write_internal(&index);
						return;
					}

					add_entry_dumped(reinterpret_cast<std::uintptr_t>(str));

					write_type(DUMP_TYPE_STRING);
					write_existing(DUMP_EXISTING);

					write_string_internal(str);
				}
				else
				{
					write_type(DUMP_TYPE_STRING);
					write_existing(DUMP_NONEXISTING);
				}
			}

			void dump_string(const char* s)
			{
				dump_string(const_cast<char*>(s));
			}

			template <typename T>
			void dump_asset(T* asset)
			{
				if (asset && asset->name)
				{
					if (is_entry_dumped(reinterpret_cast<std::uintptr_t>(asset)))
					{
						write_type(DUMP_TYPE_OFFSET);
						std::uint32_t index = get_entry_dumped_index(reinterpret_cast<std::uintptr_t>(asset));
						write_internal(&index);
						return;
					}

					add_entry_dumped(reinterpret_cast<std::uintptr_t>(asset));

					write_type(DUMP_TYPE_ASSET);
					write_existing(DUMP_EXISTING);

					write_string_internal(asset->name);
				}
				else
				{
					write_type(DUMP_TYPE_ASSET);
					write_existing(DUMP_NONEXISTING);
				}
			}

			template <typename T>
			void dump_array(T* data, std::uint32_t array_size)
			{
				if (data && array_size)
				{
					if (is_entry_dumped(reinterpret_cast<std::uintptr_t>(data)))
					{
						write_type(DUMP_TYPE_OFFSET);
						std::uint32_t index = get_entry_dumped_index(reinterpret_cast<std::uintptr_t>(data));
						write_internal(&index);
						return;
					}

					add_entry_dumped(reinterpret_cast<std::uintptr_t>(data));

					write_type(DUMP_TYPE_ARRAY);
					write_existing(DUMP_EXISTING);

					write_internal(&array_size);
					write_array_internal(data, array_size);
				}
				else
				{
					write_type(DUMP_TYPE_ARRAY);
					write_existing(DUMP_NONEXISTING);
				}
			}

			template <typename T>
			void dump_array(const T* data, std::uint32_t array_size)
			{
				dump_array<T>(const_cast<T*>(data), array_size);
			}

			template <typename T>
			void dump_single(T* asset)
			{
				dump_array<T>(asset, 1);
			}

			template <typename T>
			void dump_raw(T* data, std::uint32_t size)
			{
				if (data && size)
				{
					if (is_entry_dumped(reinterpret_cast<std::uintptr_t>(data)))
					{
						write_type(DUMP_TYPE_OFFSET);
						std::uint32_t index = get_entry_dumped_index(reinterpret_cast<std::uintptr_t>(data));
						write_internal(&index);
						return;
					}

					add_entry_dumped(reinterpret_cast<std::uintptr_t>(data));

					write_type(DUMP_TYPE_RAW);
					write_existing(DUMP_EXISTING);

					write_internal(&size);
					write_internal(data, size, 1);
				}
				else
				{
					write_type(DUMP_TYPE_RAW);
					write_existing(DUMP_NONEXISTING);
				}
			}
		};
	}
}