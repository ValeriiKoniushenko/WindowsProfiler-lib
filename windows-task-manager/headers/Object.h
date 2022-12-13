#pragma once

/**
 * @brief The base class for setting params to all objects
 */
class Object
{
public:
	virtual ~Object() = default;
	Object(const Object&) = default;
	Object& operator=(const Object&) = default;
	Object(Object&&) = default;
	Object& operator=(Object&&) = default;

	/**
	 * @brief Try to clear data for overloaded operator= and for copy\move constructs
	 * @return void
	 * @param void
	 */
	virtual void ClearData() = 0;

protected:
	Object() = default;
};