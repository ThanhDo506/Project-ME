#ifndef MANAGER_H
#define MANAGER_H

#define SINGLETON(type_name) \
	public:\
	static type_name& instance();\
	private:\
	type_name(const type_name& obj) = delete;\
	void operator=(const type_name& obj) = delete;\
	type_name() = default;\


#endif