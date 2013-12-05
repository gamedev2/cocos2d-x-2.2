@echo off
@rem =============================
@rem create a new project
@rem =============================
@rem .
@rem 定义默认公司名称和默认项目名称
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
@echo   create a new project [创建一个新项目(工程)]
@echo ================================================
@echo.
@echo Select your language / 选择您的语言:
@echo.
@echo 1. Simplified Chinese  (简体中文, default)
@echo 2. Traditional Chinese (繁體中文)
@echo 3. English
@echo.
@echo ==============================================
@echo.
@set /p language=Please input your language: 
@echo.
@if not DEFINED language (set language=1)
@if %language%==1 (echo 你的选择: 简体中文)
@if %language%==2 (echo 你的選擇: 繁體中文)
@if %language%==3 (echo Your choice: English)
@echo.
@if %language%==2 (goto CREATE_PROJECT_TW)
@if %language%==3 (goto CREATE_PROJECT_EN) else (goto CREATE_PROJECT_CN)
@goto END

:CREATE_PROJECT_CN
@echo ========================================================================
@echo.
@echo 运行 create_project.bat 命令，并指定项目的 package name：
@echo.
@echo 例如: create_project.bat com.mycompany.games.game01
@echo.
@echo       [mycompany] 是你的公司名称, [game01] 是你的项目(工程)名称.
@echo.
@echo ========================================================================
@echo.
@set mycompany_prompt=请输入您的公司名称: 
@set projectname_prompt=请输入您的项目(工程)名称: 
@goto CREATE_PROJECT_SUB

:CREATE_PROJECT_TW
@echo ========================================================================
@echo.
@echo 運行 create_project.bat 命令，並指定項目的 package name：
@echo.
@echo 例如: create_project.bat com.mycompany.games.game01
@echo.
@echo       [mycompany] 是你的公司名稱, [game01] 是你的項目(工程)名稱.
@echo.
@echo ========================================================================
@echo.
@set mycompany_prompt=請輸入您的公司名稱: 
@set projectname_prompt=請輸入您的項目(工程)名稱: 
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
