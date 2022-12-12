#pragma once

class Object
{
public:
	virtual ~Object() = default;
	Object(const Object&) = default;
	Object& operator=(const Object&) = default;
	Object(Object&&) = default;
	Object& operator=(Object&&) = default;

	virtual void ClearData() = 0;

protected:
	Object() = default;
};