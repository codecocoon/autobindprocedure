# auto bind procedure
auto bind procedure는packet opcode와 packet procedure function을 자동으로 bind 합니다.




# 요약
    서버가 packet을 받으면 이를 처리할 수 있는 procedure function을 호출하고 packet을 처리합니다.
    이때, packet opcode로 procedure function을 찾기 위해 packet opcode와 procedure function을 bind해야 합니다.
    대부분 switch, std::map, std::function, boost::function 등을 사용합니다.
    이러한 수동 방식에 단점은 복사 붙이기로 만드는데, 
    프로그래머 집중력이 떨어지면 packet opcode를 다른 procedure function과 bind 할 수도 있고
    bind 코드를 누락시키는 경우도 있습니다.
    이러한 단점을 없애기 위해 자동으로 bind 해주는 "auto bind procedure"를 만들었습니다.




# 내용
[수동 바인드 방식중 switch]

    enum packetopcode
    {
        packetopcode_login,
        packetopcode_logout,
    };

    void messageproc( const packetopcode in_opcode, const int in_data )
    {
        //아래 코드가 packet opcode와 procedure function을 bind하는 부분으로
        //std::map이나 boost::bind등도 이것과 다른 모습이지만 이처럼 bind를 하는 부분이 있습니다.
        switch( in_opcode )
        {
            case packetopcode_login : proc_login( in_data ); break;
            case packetopcode_logout : proc_logout( in_data); break;
            default: std::cout << "bad packet opcode" << std::endl;
        }
        return;
    }

    void proc_login( const int in_data)
    {
        std::cout << "run : proc_login" << std::endl;
        return;
    }

    void proc_logout(const int in_data)
    {
        std::cout << "run : proc_logout" << std::endl;
        return;
    }

    int main(int argc, _TCHAR* argv[])
    {
        messageproc( packetopcode_login, 1 );
        messageproc( packetopcode_login, 100 );
        return 0;
    }




[자동 바인드 방식]

    enum packetopcode
    {
        packetopcode_login,
        packetopcode_logout,
    };

    //register_procunit 매크로가 bind를 자동으로 합니다.
    register_procunit( packetopcode_login )
    {
        bool run( const int in_data )
        {
            int sum = in_data + 1;
            std::cout << "run : packetopcode_login || "
                << lh( in_data, sum )
                << std::endl;
            return true;
        }
    }
    
    register_procunit( packetopcode_logout )
    {
        bool run( const int in_data )
        {
            int sum = in_data + 2;
            std::cout << "run : packetopcode_logout || "
                << lh( in_data, sum )
                << std::endl;       
            return true;
        }
    }

    int main(int argc, _TCHAR* argv[])
    {
        g_procframework_manager()->get_procunit( packetopcode_login )->run( 1 );
        g_procframework_manager()->get_procunit( packetopcode_logout )->run( 100 );
        return 0;
    }



# 사용방법
    msvc++로 만든 프로젝트를 열고 원리를 습득한 후에 사용해야 합니다.
    
