#pragma once

class cell;
class CDetector
{
	friend class cell;
public:
	CDetector(void);
public:
	~CDetector(void);
private:
	UINT id;
	UINT count;
	UINT cellid;
	bool hasd;
};
