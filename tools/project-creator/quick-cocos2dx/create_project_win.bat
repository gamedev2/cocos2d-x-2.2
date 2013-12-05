@echo off
@rem =============================
@rem create a new project
@rem =============================
@rem .
@rem ����Ĭ�Ϲ�˾���ƺ�Ĭ����Ŀ����
@rem .
@rem set default_companyname=quick_cocos2dx
@set default_companyname=houyisoft
@set default_projectname=helloworld
@set create_project_bat=create_project.bat
@rem =============================
@echo on
@echo.
@echo ================================================
@echo   Quick Cocos2d-x
@echo   create a new project [����һ������Ŀ(����)]
@echo ================================================
@echo.
@echo Select your language / ѡ����������:
@echo.
@echo 1. Simplified Chinese  (��������, default)
@echo 2. Traditional Chinese (���w����)
@echo 3. English
@echo.
@echo ==============================================
@echo.
@set /p language=Please input your language: 
@echo.
@if not DEFINED language (set language=1)
@if %language%==1 (echo ���ѡ��: ��������)
@if %language%==2 (echo ����x��: ���w����)
@if %language%==3 (echo Your choice: English)
@echo.
@if %language%==2 (goto CREATE_PROJECT_TW)
@if %language%==3 (goto CREATE_PROJECT_EN) else (goto CREATE_PROJECT_CN)
@goto END

:CREATE_PROJECT_CN
@echo ========================================================================
@echo.
@echo ���� create_project.bat �����ָ����Ŀ�� package name��
@echo.
@echo ����: create_project.bat com.mycompany.games.game01
@echo.
@echo       [mycompany] ����Ĺ�˾����, [game01] �������Ŀ(����)����.
@echo.
@echo ========================================================================
@echo.
@set mycompany_prompt=���������Ĺ�˾����: 
@set projectname_prompt=������������Ŀ(����)����: 
@goto CREATE_PROJECT_SUB

:CREATE_PROJECT_TW
@echo ========================================================================
@echo.
@echo �\�� create_project.bat ����Kָ���Ŀ�� package name��
@echo.
@echo ����: create_project.bat com.mycompany.games.game01
@echo.
@echo       [mycompany] ����Ĺ�˾���Q, [game01] ������Ŀ(����)���Q.
@echo.
@echo ========================================================================
@echo.
@set mycompany_prompt=Ոݔ�����Ĺ�˾���Q: 
@set projectname_prompt=Ոݔ�������Ŀ(����)���Q: 
@goto CREATE_PROJECT_SUB

:CREATE_PROJECT_EN
@echo ========================================================================
@echo.
@echo run create_project.bat command, and specify the project package name:
@echo.
@echo example: create_project.bat com.mycompany.games.game01
@echo.
@echo          [mycompany] is your company's name, [game01] is project name.
@echo.
@echo ========================================================================
@echo.
@set mycompany_prompt=Please input your company name: 
@set projectname_prompt=Please input your project name: 
@goto CREATE_PROJECT_SUB

:CREATE_PROJECT_SUB
@set /p mycompany=%mycompany_prompt%
@if not DEFINED mycompany (echo %default_companyname%)
@if not DEFINED mycompany (set mycompany=%default_companyname%)
@echo.
@set /p projectname=%projectname_prompt%
@if not DEFINED projectname (echo %default_projectname%)
@if not DEFINED projectname (set projectname=%default_projectname%)
@echo.
@set packagename=com.%mycompany%.games.%projectname%
@echo Dos Command: %create_project_bat% %packagename%
%create_project_bat% %packagename%
@goto END

:END
@echo end.
@echo on
pause
