#pragma once
#include<math.h>

template<typename T> class Counter {

public:
	Counter(int max) { m_count = 0, m_countMax = max; };
	virtual ~Counter() {};

	T operator + (T t) { return min(m_count + t, m_countMax); }
	T operator - (T t) { return max(m_count - t, 0); }
	T operator += (T t) { return m_count = (m_count + t); }
	T operator -= (T t) { return m_count = (m_count - t); }
	T operator = (T t) { return m_count = t; }

	// �ő�Ȃ�true��Ԃ�
	bool IsMax() { m_count == m_countMax; }

	// 0�`1�ōő�܂ł̊�����Ԃ�
	float GetPercent() { return (float)m_count / (float)m_countMax; };

private:
	T m_count;
	T m_countMax;

};