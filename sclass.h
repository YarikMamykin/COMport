class STRING
{
	public: char* value;
	public: int length;
	
	public: STRING(){};
	public: ~STRING(){};
	
	public: STRING(char* Value)
	{
		this->value = Value;
		this->length = this->GetLength();
	}
	
	public: const int GetLength()
	{
		int i = 0; 
		int n = 0;
		if(this->value[i] == '\0') return 0;
		while(this->value[i] != '\0') {i++;if(this->value[i] == '\t') n++;}
		return (i + n*8);
	}
	
	public: void DelChar(int num)
	{
		this->length = this->GetLength();
		if(this->length < num)
			return;
		else
			this->value[num] = '\0';
		return;
	}
	
	public: void ValueChanged()
	{
		if(this->value == NULL) return;
		this->length = this->GetLength();
		return;
	}
	
	public: friend const STRING operator+(STRING& LeftString, STRING& RightString)
	{
		int* n = new int(0);				
		static const int buffl = LeftString.GetLength() + RightString.GetLength();		
		static char buff[256];
		
		for(int i = 0; i < LeftString.GetLength(); i++)
		{buff[i] = LeftString.value[i];}
		
		for(int i = LeftString.GetLength(); i < buffl; i++)
		{buff[i] = *(RightString.value+*n); (*n)++;}
	
		LeftString.value = buff;
		
		LeftString.length = LeftString.GetLength();
	
		delete n;		
		return LeftString;
	}
	
	public: friend const STRING operator+(STRING& LeftString, char RightChar)
	{
		int* n = new int(0);
		int* buffl = new int(LeftString.GetLength() + 1);
		char* buff = new char[*buffl];
		
		for(int i = 0; i < LeftString.GetLength(); i++)
		{buff[i] = *(LeftString.value+i); if(i == LeftString.GetLength() - 1) buff[i+1] = RightChar;}
		
		LeftString.value = buff;
	
		LeftString.length = LeftString.GetLength();
		
		delete n;
		delete buffl;
		delete buff;
		return LeftString;
	}	
};

STRING NullSTRING;
int getlen(const char* str)
{ 
	int* len = new int(0);
	for(int i = 0; str[i] != '\0' && str[i] < 127; i++)
	{(*len)++;}
	return *len; 	
}
