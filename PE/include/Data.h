#ifndef DATA_H
#define DATA_H


class Data
{
	public:
		Data();
		virtual ~Data();
	protected:
	private:
		bool average;
	void Set_average();
	struct Pic {
		int x;
		int y;
		int t;
	};
};

#endif // DATA_H
