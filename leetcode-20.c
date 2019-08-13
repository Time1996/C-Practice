//转录于https://leetcode-cn.com/problems/valid-parentheses/solution/cyu-yan-jian-jian-dan-dan-de-ji-xing-dai-ma-jie-14/
bool isValid(char * s){
    if(s == NULL || s[0] == '\0')return true;
    char stack[10240];int top = 0;
    for(int i = 0; s[i]; ++i)
    {
        if(s[i] == '(' || s[i] == '[' || s[i] == '{')stack[top++] = s[i];
        else{
            if((--top)<0)return false;//先减减，让top指向栈顶元素
            if(s[i] == ')' && stack[top] != '(')return false;
            if(s[i] == ']' && stack[top] != '[')return false;
            if(s[i] == '}' && stack[top] != '{')return false;
        }
    }
    return (top?false:true);//防止"["这种类似情况
}