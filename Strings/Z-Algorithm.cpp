    string s;
    cin >> s;
    int n = s.size();
    vi z(n);

    int x=0, y=0;
    for(int i=1; i<n; i++)
    {
        if(i <= y)
            z[i] = min(z[i-x], y-i+1);
        while( z[i] + i < n && s[z[i]] == s[z[i] + i])
            ++z[i];
        if(i+z[i]-1 > y)
        {
            x = i; y = i+z[i]-1;
        }
    }
    for(auto e:z)
        cout << e << " ";