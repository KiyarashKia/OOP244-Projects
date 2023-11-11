#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H
namespace sdds {

	class Status {
		char* descStatus;
		int statCode;

	public:
		Status(const char* description = nullptr);

		Status(const Status& other); // RO3
		Status& operator=(const Status& other); // RO3
		~Status(); /// RO3

		Status& operator=(int newCode);
		Status& operator=(const char* newDesc);

		operator int() const;
		operator const char* () const;
		operator bool() const;

		Status& clear();
	};

	std::ostream& operator<<(std::ostream& os, const Status& st);


}

#endif // !SDDS_STATUS_H