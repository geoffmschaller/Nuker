#include <stdio.h>
#include <windows.h>

int
main(void)
{
	HANDLE device = NULL;
	device = CreateFile(
			"z:/",
			GENERIC_ALL,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);
	if (!device)
	{
		printf("Could not find drive. ");
		return 1;
	}
	long long lpFreeBytesAvailable, lpTotalNumberOfBytes, lpTotalNumberOfFreeBytes;
	int result = GetDiskFreeSpaceEx(
			"z:/",
			(PULARGE_INTEGER) &lpFreeBytesAvailable,
			(PULARGE_INTEGER) &lpTotalNumberOfBytes,
			(PULARGE_INTEGER) &lpTotalNumberOfFreeBytes
	);
	if (!result)
	{
		printf("Error getting size\n");
		unsigned long error_code = GetLastError();
		printf("Error: %lu", error_code);
		return 1;
	}
	printf("Free Bytes Available: %lld\n", lpFreeBytesAvailable);
	printf("Total Number of Bytes: %lld\n", lpTotalNumberOfBytes);
	printf("Total Number of Free Bytes: %lld\n", lpTotalNumberOfFreeBytes);
	BYTE sector[512] = {0};
	DWORD bytesWritten;
	int write_file = WriteFile(
			device,
			sector,
			512,
			&bytesWritten,
			NULL
	);
	if (!write_file)
	{
		printf("Error Code: ");
		DWORD error_code = GetLastError();
		printf("%lu", error_code);
	}
	printf("%lu", bytesWritten);
	CloseHandle(device);

	return 0;
}