#include "stdafx.h"
#include "Houjie.h"

#include "arrayW.h"
#include "vectorW.h"
#include "listW.h"

Houjie::Houjie()
{
}


Houjie::~Houjie()
{
}

void Houjie::testAll()
{
	if (0)
	{
		arrayW array0;
		array0.test_array();

		vectorW vector0;
		long value = 100;
		vector0.test_vector(value);
	}

	listW list0;
	long value = 100;
	list0.test_list(value);
}
