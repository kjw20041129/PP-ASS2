import subprocess
import os

def test_maze_load():
    #测试能否正常读取格式正确的迷宫
    test_file_path = os.path.join(os.path.dirname(__file__), "test_data", "mazes", "valid", "reg_5x5.txt")
    #生成绝对路径

    process = subprocess.Popen(["./maze_game", test_file_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    stdout, stderr = process.communicate()

    if process.returncode == 0:
        print("程序运行成功")
        print("输出：")
        print(stdout)
        
        # 定义预期的迷宫布局
        expected_output = [
            "#####",
            "#S  #",
            "#  ##",
            "# E##",
            "#####"
        ]
        
         # 将程序的输出按行分割，并去除空白行
        output_lines = [line.strip() for line in stdout.strip().split('\n') if line.strip()]
            
        # 检查输出的行数是否与预期一致
        if len(output_lines) != len(expected_output):
            print("测试失败：输出的行数与预期不符")
            return
            
        # 检查每一行是否与预期输出一致
        for expected_line, output_line in zip(expected_output, output_lines):
            if expected_line != output_line:
                print(f"测试失败：预期输出 '{expected_line}'，但实际输出 '{output_line}'")
                return
        
        print("测试成功：迷宫文件加载正确")
    else:
        print("程序运行失败")
        print("错误：")
        print(stderr)



def test_invalid_width_maze():
    #测试读取无效宽度的迷宫
    #测试文件的绝对路径
    test_file_path = os.path.join(os.path.dirname(__file__), "test_data", "mazes", "invalid", "ireg_width_5x5.txt")
    
    try:
        #运行程序，传递迷宫路径
        process = subprocess.Popen(["./maze_game", test_file_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        stdout, stderr = process.communicate()
        
        #检查返回码
        if process.returncode != 0:
            print("程序正确处理了无效宽度的迷宫")
            print("错误输出：")
            print(stderr)
        else:
            print("程序未正确处理无效宽度的迷宫")
            print("程序输出：")
            print(stdout)
    except Exception as e:
        print(f"测试发生异常：{e}")

def test_invalid_height_maze():
    #测试无效高度的迷宫
    
    #测试文件绝对路径
    test_file_path = os.path.join(os.path.dirname(__file__), "test_data", "mazes", "invalid", "ireg_height_5x5.txt")
    
    try:
        #运行程序，传递迷宫路径
        process = subprocess.Popen(["./maze_game", test_file_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        stdout, stderr = process.communicate()
        
        #检查返回码
        if process.returncode != 0:
            print("程序正确处理了无效高度的迷宫")
            print("错误输出：")
            print(stderr)
        else:
            print("程序未正确处理无效高度的迷宫")
            print("程序输出：")
            print(stdout)
    except Exception as e:
        print(f"测试发生异常：{e}")

def test_maze_too_small():
    #测试迷宫尺寸小于最小值（5x5）
    test_file_path = os.path.join(os.path.dirname(__file__), "test_data", "mazes", "invalid", "too_small_4x4.txt")
    
    process = subprocess.Popen(["./maze_game", test_file_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    stdout, stderr = process.communicate()
    
    if process.returncode != 0 and "Maze size is too small. Minimum size is 5x5." in stderr:
        print("测试成功：程序正确处理了尺寸过小的迷宫")
    else:
        print("测试失败：程序未正确处理尺寸过小的迷宫")
        print("程序输出：")
        print(stdout)
        print("错误输出：")
        print(stderr)


def test_maze_too_large():
    #测试迷宫尺寸大于最大值（100x100）
    test_file_path = os.path.join(os.path.dirname(__file__), "test_data", "mazes", "invalid", "too_large_101x101.txt")
    
    process = subprocess.Popen(["./maze_game", test_file_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    stdout, stderr = process.communicate()
    
    if process.returncode != 0 and "Maze size is too large. Maximum size is 100x100." in stderr:
        print("测试成功：程序正确处理了尺寸过大的迷宫")
    else:
        print("测试失败：程序未正确处理尺寸过大的迷宫")
        print("程序输出：")
        print(stdout)
        print("错误输出：")
        print(stderr)

def test_invalid_S_maze():
    #测试没有起点 S 的迷宫文件
    
    # 测试文件的绝对路径
    test_file_path = os.path.join(os.path.dirname(__file__), "test_data", "mazes", "invalid", "ireg_no_S.txt")
    
    try:
        # 运行程序，传递迷宫路径
        process = subprocess.Popen(["./maze_game", test_file_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        stdout, stderr = process.communicate()
        
        # 检查返回码
        if process.returncode != 0:
            # 检查是否包含没有S的信息
            if "The maze lacks a starting point S" in stderr:
                print("测试成功：程序正确处理了没有起点 S 的迷宫")
                print("错误输出：")
                print(stderr)
            else:
                print("测试失败：程序未正确报告错误信息")
                print("错误输出：")
                print(stderr)
        else:
            print("测试失败：程序未正确处理没有起点 S 的迷宫")
            print("程序输出：")
            print(stdout)
    except Exception as e:
        print(f"测试发生异常：{e}")
def test_invalid_E_maze():
    #测试没有终点 E 的迷宫文件

    test_file_path = os.path.join(os.path.dirname(__file__),"test_data", "mazes", "invalid", "ireg_no_E.txt")
    
    try:
        process = subprocess.Popen(["./maze_game", test_file_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        stdout, stderr = process.communicate()

        #检查返回码
        if process.returncode != 0:
            #检查是否包含没有E的信息
            if "The maze lacks an ending point E" in stderr:
                print("测试成功：程序正确处理了没有终点 E 的迷宫")
                print("错误输出：")
                print(stderr)
            else:
                print("测试失败：程序未正确报告错误信息")
                print("错误输出：")
                print(stderr)
        else:
            print("测试失败：程序未正确处理没有终点 E 的迷宫")
            print("程序输出：")
            print(stdout)
    except Exception as e:
        print(f"测试发生异常：{e}")


def test_invalid_file():
    #测试无效文件
    test_file_path = os.path.join(os.path.dirname(__file__), "test_data", "invalid", "invalid_file_maze.jpg")
    try:
        process = subprocess.Popen(["./maze_game", test_file_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        stdout, stderr = process.communicate()
        
        # 检查返回码
        if process.returncode != 0:
            # 检查是否包含非法迷宫文件格式的错误信息
            if "Invalid file format. Only .txt files are supported." in stderr:
                print("测试成功：程序正确处理了无效文件格式")
                print("错误输出：")
                print(stderr)
            else:
                print("测试失败：程序未正确报告错误信息")
                print("错误输出：")
                print(stderr)
        else:
            print("测试失败：程序未正确处理无效文件格式")
            print("程序输出：")
            print(stdout)
    except Exception as e:
        print(f"测试发生异常：{e}")

def run_maze_game_with_input(maze_file, input_file):
    
    #运行迷宫游戏并提供输入文件，return标准流输出和标准错误
    
    maze_path = os.path.join(os.path.dirname(__file__), maze_file)
    input_path = os.path.join(os.path.dirname(__file__), input_file)
    
    try:
        with open(input_path, 'r') as infile:
            process = subprocess.Popen(["./maze_game", maze_path], stdin=infile, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
            stdout, stderr = process.communicate()
    except Exception as e:
        print(f"运行程序时发生异常：{e}")
        return None, None
    
    return stdout, stderr
"""





玩家输入测试





"""
def test_invalid_input():
    # 测试玩家输入非法字符（如非WASDQM的字符）
    maze_file = "test_data/mazes/valid/reg_5x5.txt"
    input_file = "test_data/inputs/invalid_input.txt"  # 输入文件包含非法字符 "X"
    
    stdout, stderr = run_maze_game_with_input(maze_file, input_file)
    
    if stdout is None:
        print("测试失败：无法运行程序")
        return
    
    # 检查程序是否正确提示输入无效
    expected_output = "Invalid input. Please enter W/A/S/D/M/Q."
    
    output_lines = stdout.strip().split('\n')
    
    success = False
    for line in output_lines:
        if expected_output in line:
            success = True
            break
    
    if success:
        print("测试成功：程序正确处理了非法输入")
    else:
        print("测试失败：程序未正确处理非法输入")
        print("程序输出：")
        print(stdout)
        if stderr:
            print("错误输出：")
            print(stderr)

def test_player_move_up_uppercase():
    #测试玩家向上移动（大写W）
    stdout, stderr = run_maze_game_with_input("test_data/mazes/valid/reg_movement.txt", "test_data/inputs/move_up_uppercase.txt")
    
    if "Player position: (4, 3)" in stdout:
        print("测试成功：玩家向上移动正确（大写W）")
    else:
        print("测试失败：玩家向上移动错误（大写W）")
        print("程序输出：")
        print(stdout)

def test_player_move_up_lowercase():
    #测试玩家向上移动（小写w）
    stdout, stderr = run_maze_game_with_input("test_data/mazes/valid/reg_movement.txt", "test_data/inputs/move_up_lowercase.txt")
    
    if "Player position: (4, 3)" in stdout:
        print("测试成功：玩家向上移动正确（小写w）")
    else:
        print("测试失败：玩家向上移动错误（小写w）")
        print("程序输出：")
        print(stdout)

def test_player_move_down_uppercase():
    #测试玩家向下移动（大写S）
    stdout, stderr = run_maze_game_with_input("test_data/mazes/valid/reg_movement.txt", "test_data/inputs/move_down_uppercase.txt")
    
    if "Player position: (4, 5)" in stdout:
        print("测试成功：玩家向下移动正确（大写S）")
    else:
        print("测试失败：玩家向下移动错误（大写S）")
        print("程序输出：")
        print(stdout)

def test_player_move_down_lowercase():
    #测试玩家向下移动（小写s
    stdout, stderr = run_maze_game_with_input("test_data/mazes/valid/reg_movement.txt", "test_data/inputs/move_down_lowercase.txt")
    
    if "Player position: (4, 5)" in stdout:
        print("测试成功：玩家向下移动正确（小写s）")
    else:
        print("测试失败：玩家向下移动错误（小写s）")
        print("程序输出：")
        print(stdout)

def test_player_move_left_uppercase():
    #测试玩家向左移动（大写A）
    stdout, stderr = run_maze_game_with_input("test_data/mazes/valid/reg_movement.txt", "test_data/inputs/move_left_uppercase.txt")
    
    if "Player position: (3, 4)" in stdout:
        print("测试成功：玩家向左移动正确（大写A）")
    else:
        print("测试失败：玩家向左移动错误（大写A）")
        print("程序输出：")
        print(stdout)

def test_player_move_left_lowercase():
    #测试玩家向左移动（小写a）
    stdout, stderr = run_maze_game_with_input("test_data/mazes/valid/reg_movement.txt", "test_data/inputs/move_left_lowercase.txt")
    
    if "Player position: (3, 4)" in stdout:
        print("测试成功：玩家向左移动正确（小写a）")
    else:
        print("测试失败：玩家向左移动错误（小写a）")
        print("程序输出：")
        print(stdout)

def test_player_move_right_uppercase():
    #测试玩家向右移动（大写D）
    stdout, stderr = run_maze_game_with_input("test_data/mazes/valid/reg_movement.txt", "test_data/inputs/move_right_uppercase.txt")
    
    if "Player position: (5, 4)" in stdout:
        print("测试成功：玩家向右移动正确（大写D）")
    else:
        print("测试失败：玩家向右移动错误（大写D）")
        print("程序输出：")
        print(stdout)

def test_player_move_right_lowercase():
    #测试玩家向右移动（小写d）
    stdout, stderr = run_maze_game_with_input("test_data/mazes/valid/reg_movement.txt", "test_data/inputs/move_right_lowercase.txt")
    
    if "Player position: (5, 4)" in stdout:
        print("测试成功：玩家向右移动正确（小写d）")
    else:
        print("测试失败：玩家向右移动错误（小写d）")
        print("程序输出：")
        print(stdout)

def test_player_position_with_X():
    #测试玩家位置是否用 X 表示
    maze_file = "test_data/mazes/valid/reg_5x5.txt"
    input_file = "test_data/inputs/move_right_lowercase.txt"
    
    stdout, stderr = run_maze_game_with_input(maze_file, input_file)
    
    if stdout is None:
        print("测试失败：无法运行程序")
        return
    
    # 检查玩家位置是否用 X 表示
    expected_output = [
        "#####",
        "#SX #",
        "#  ##",
        "# E##",
        "#####"
    ]
    
    output_lines = stdout.strip().split('\n')
    
    success = True
    for expected_line, output_line in zip(expected_output, output_lines):
        if expected_line != output_line:
            success = False
            print(f"测试失败：预期输出 '{expected_line}'，但实际输出 '{output_line}'")
            break
    
    if success:
        print("测试成功：玩家位置正确地用 X 表示")
    else:
        print("测试失败：玩家位置未正确地用 X 表示")
        print("程序输出：")
        print(stdout)
        if stderr:
            print("错误输出：")
            print(stderr)

def test_wall_boundary():
    #测试玩家被墙包围时的移动
    stdout, stderr = run_maze_game_with_input("test_data/mazes/valid/surrounded_by_walls.txt", "test_data/inputs/move_all_directions.txt")
    
    expected_output = [
        "Cannot move through walls.",
        "Cannot move through walls.",
        "Cannot move through walls.",
        "Cannot move through walls."
    ]
    
    output_lines = stdout.strip().split('\n')
    
    success = True
    for expected in expected_output:
        if expected not in output_lines:
            success = False
            break
    
    if success:
        print("测试成功：玩家被墙包围时无法移动")
    else:
        print("测试失败：玩家被墙包围时移动错误")
        print("程序输出：")
        print(stdout)
        if stderr:
            print("错误输出：")
            print(stderr)

def test_maze_boundary():
    # 测试地图边界
    stdout, stderr = run_maze_game_with_input("test_data\mazes\valid\boundary_test.txt", "test_data/inputs/move_to_boundaries.txt")
    
    expected_output = "Cannot move outside the maze boundary."
    
    output_lines = stdout.strip().split('\n')
    
    success = False
    for line in output_lines:
        if expected_output in line:
            success = True
            break
    
    if success:
        print("测试成功：玩家不能向上移动出边界")
    else:
        print("测试失败：玩家向上移动出边界时未正确提示")
        print("程序输出：")
        print(stdout)
        if stderr:
            print("错误输出：")
            print(stderr)


def test_print_maze_with_M_uppercase():
    # 测试玩家输入大写 M 时打印当前迷宫
    maze_file = "test_data/mazes/valid/reg_5x5.txt"
    input_file = "test_data/inputs/print_maze_with_M_uppercase.txt"  # 输入文件包含 "M"

    stdout, stderr = run_maze_game_with_input(maze_file, input_file)

    if stdout is None:
        print("测试失败：无法运行程序")
        return

    # 定义玩家移动后迷宫的预期输出（假设玩家初始位置为 S，输入 M 后打印当前迷宫）
    expected_output = [
        "#####",
        "#S  #",
        "#  ##",
        "# E##",
        "#####"
    ]

    output_line = stdout.strip().split('\n')

    success = True
    for expected_line, output_line in zip(expected_output, output_line ):
        if expected_line != output_line:
            success = False
            print(f"测试失败：预期输出 '{expected_line}'，但实际输出 '{output_line}'")
            break

    if success:
        print("测试成功：玩家输入大写 M 时正确打印了当前迷宫")
    else:
        print("测试失败：玩家输入大写 M 时未正确打印当前迷宫")
        print("程序输出：")
        print(stdout)
        if stderr:
            print("错误输出：")
            print(stderr)


def test_print_maze_with_M_lowercase():
    # 测试玩家输入小写 m 时打印当前迷宫
    maze_file = "test_data/mazes/valid/reg_5x5.txt"
    input_file = "test_data/inputs/print_maze_with_M_lowercase.txt"  # 输入文件包含 "m"

    stdout, stderr = run_maze_game_with_input(maze_file, input_file)

    if stdout is None:
        print("测试失败：无法运行程序")
        return

    # 定义玩家移动后迷宫的预期输出（假设玩家初始位置为 S，输入 m 后打印当前迷宫）
    expected_output = [
        "#####",
        "#S  #",
        "#  ##",
        "# E##",
        "#####"
    ]

    output_line = stdout.strip().split('\n')

    success = True
    for expected_line, output_line in zip(expected_output, output_line):
        if expected_line != output_line:
            success = False
            print(f"测试失败：预期输出 '{expected_line}'，但实际输出 '{output_line}'")
            break

    if success:
        print("测试成功：玩家输入小写 m 时正确打印了当前迷宫")
    else:
        print("测试失败：玩家输入小写 m 时未正确打印当前迷宫")
        print("程序输出：")
        print(stdout)
        if stderr:
            print("错误输出：")
            print(stderr)

def test_win():
    #测试玩家到达终点后游戏获胜
    maze_file = "test_data/mazes/valid/test_win.txt"
    input_file = "test_data/inputs/move_right_twice.txt"
    
    stdout, stderr = run_maze_game_with_input(maze_file, input_file)
    
    if stdout is None:
        print("测试失败：无法运行程序")
        return
    
    # 检查游戏是否提示获胜
    expected_output = "Congratulations! You've won!"
    
    output_lines = stdout.strip().split('\n')
    
    success = False
    for line in output_lines:
        if expected_output in line:
            success = True
            break
    
    if success:
        print("测试成功：玩家到达终点 E 后游戏获胜")
    else:
        print("测试失败：玩家到达终点 E 后未正确提示获胜")
        print("程序输出：")
        print(stdout)
        if stderr:
            print("错误输出：")
            print(stderr)


def test_quit_uppercase():
    print("测试玩家中途退出游戏（大写Q）...")
    maze_file = "test_data/mazes/valid/reg_5x5.txt"
    input_file = "test_data/inputs/quit_game_uppercase.txt"
    
    stdout, stderr = run_maze_game_with_input(maze_file, input_file)
    
    if stdout is None:
        print("测试失败：无法运行程序")
        return
    
    # 检查游戏是否正确提示退出
    expected_output = "Game over. You quit."
    
    output_lines = stdout.strip().split('\n')
    
    success = False
    for line in output_lines:
        if expected_output in line:
            success = True
            break
    
    if success:
        print("测试成功：玩家中途退出游戏（大写Q）")
    else:
        print("测试失败：玩家中途退出游戏时未正确提示（大写Q）")
        print("程序输出：")
        print(stdout)
        if stderr:
            print("错误输出：")
            print(stderr)


def test_quit_lowercase():
    print("测试玩家中途退出游戏（小写q）...")
    maze_file = "test_data/mazes/valid/reg_5x5.txt"
    input_file = "test_data/inputs/quit_game_lowercase.txt"
    
    stdout, stderr = run_maze_game_with_input(maze_file, input_file)
    
    if stdout is None:
        print("测试失败：无法运行程序")
        return
    
    # 检查游戏是否正确提示退出
    expected_output = "Game over. You quit."
    
    output_lines = stdout.strip().split('\n')
    
    success = False
    for line in output_lines:
        if expected_output in line:
            success = True
            break
    
    if success:
        print("测试成功：玩家中途退出游戏（小写q）")
    else:
        print("测试失败：玩家中途退出游戏时未正确提示（小写q）")
        print("程序输出：")
        print(stdout)
        if stderr:
            print("错误输出：")
            print(stderr)

