#pragma once
class CBoostSharedMemory
{
public:
	CBoostSharedMemory();
	virtual ~CBoostSharedMemory();

	int file_mapping_test();
	int file_mapping_test_01();
	void thrd();
};

