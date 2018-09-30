#include <iostream>
class DateTime
{
    class DataComponent
    {
      private:
        int m_value;
        int m_min;
        int m_max;
        DataComponent *p_up;

      public:
        DataComponent(){};
        DataComponent(int value, int min, int max)
        {
            m_value = value;
            m_min = min;
            m_max = max;
            calculateValue();
        }
        int getValue() const { return m_value; }
        void calculateValue() //把值设置到有效范围
        {
            int range = m_max - m_min + 1;
            int relative = m_value - m_min;
            if (p_up)
            {
                *p_up + relative / range; //进位
            }
            m_value = relative % range + m_min;
        }
        void setUper(DataComponent *uper) { p_up = uper; }
        DataComponent &operator+(int val)
        {
            m_value += val;
            calculateValue();
            return *this;
        }
    };
    ///////////////////////////////////////
  private:
  public:
    DataComponent m_year;
    DataComponent m_month;
    DataComponent m_day;
    DataComponent m_hour;
    DateTime(int year, int month, int day, int hour)
    {
        m_year = DataComponent(year, 1000, 2050);
        m_month = DataComponent(month, 1, 12);
        m_day = DataComponent(day, 1, 30);
        m_hour = DataComponent(hour, 0, 23);
    }
};
int main()
{
    DateTime datetime(2018, 9, 29, 16);
    while (datetime.m_day.getValue() < 11)
    {
        datetime.m_hour + 1;
        std::cout << datetime.m_day.getValue() << " fdfdf  " << datetime.m_hour.getValue() << "   " << datetime.m_hour.getValue() << std::endl;
    }
    system("pause");

    return 0;
}
