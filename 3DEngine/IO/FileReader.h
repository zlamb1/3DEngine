#pragma once

#include <fstream>
#include <iostream>
#include <string>

template<typename T>
class Maybe {

public:
	Maybe(T t) {
		m_Value = t;
	}

	bool HasValue() {
		return m_HasValue; 
	}

	T GetValue() {
		return m_Value; 
	}

	static Maybe<T> Error() {
		return Maybe<T>(); 
	}

private:
	Maybe() {
		m_HasValue = false; 
	}

	T m_Value; 
	bool m_HasValue = true; 

};

static Maybe<std::string> ReadFile(std::string_view path) {
	std::ifstream req_file;
	req_file.open(path.data());
	if (!req_file.is_open()) {
		return Maybe<std::string>::Error(); 
	}

	std::string lines{}, line;
	while (std::getline(req_file, line)) {
		lines.append(line + "\n");
	}

	return Maybe(lines); 
}