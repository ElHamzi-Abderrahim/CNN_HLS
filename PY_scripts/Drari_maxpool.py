def maxpool_1(tab_in):
    tab_out=[[[0 for i in range(14)] for j in range(14)] for k in range(64)]
    for i in range(64):
        line = 1
        for F in range(14):
            tab_out[i][0][F] = 0.0
        for j in range(0, 24, 2):
            colomn = 1
            tab_out[i][line][0] = 0.0
            tab_out[i][line][13] = 0.0
            for k in range(0, 24, 2):
                tmp = 0
                if k < 22 and j < 22:
                    tmp = max(tab_in[i][j][k], tab_in[i][j][k+1],tab_in[i][j][k+2], tab_in[i][j+1][k], tab_in[i][j+1][k+1], tab_in[i][j+1][k+2],tab_in[i][j+2][k], tab_in[i][j+2][k+1], tab_in[i][j+2][k+2])
                    tab_out[i][line][colomn] = tmp
                elif k == 22 and j!=22:
                    tmp = max(tab_in[i][j][k], tab_in[i][j][k+1],tab_in[i][j+1][k], tab_in[i][j+1][k+1],tab_in[i][j+2][k], tab_in[i][j+2][k+1])
                    tab_out[i][line][colomn] = tmp
                elif j == 22 and k!=22:
                    tmp = max(tab_in[i][j][k], tab_in[i][j][k+1],tab_in[i][j][k+2], tab_in[i][j+1][k], tab_in[i][j+1][k+1], tab_in[i][j+1][k+2])
                    tab_out[i][line][colomn] = tmp
                elif k == 22 and j == 22:
                    tmp = max(tab_in[i][j][k], tab_in[i][j][k+1], tab_in[i][j+1][k], tab_in[i][j+1][k+1])
                    tab_out[i][line][colomn] = tmp
                colomn += 1
            line += 1
        for L in range(14):
            tab_out[i][13][L] = 0.0
    return tab_out
def maxpool_2(tab_in):
    tab_out=[[[0 for i in range(8)] for j in range(8)] for k in range(32)]
    for i in range(32):
        line = 1
        for F in range(8):
            tab_out[i][0][F] = 0.0
        for j in range(0, 12, 2):
            colomn = 1
            tab_out[i][line][0] = 0.0
            tab_out[i][line][7] = 0.0
            for k in range(0, 12, 2):
                tmp = 0
                if k < 10 and j < 10:
                    tmp = max(tab_in[i][j][k], tab_in[i][j][k+1], tab_in[i][j][k+2], tab_in[i][j+1][k], tab_in[i][j+1][k+1], tab_in[i][j+1][k+2], tab_in[i][j+2][k], tab_in[i][j+2][k+1], tab_in[i][j+2][k+2])
                    tab_out[i][line][colomn] = tmp
                elif k == 10 and j!=10:
                    tmp = max(tab_in[i][j][k], tab_in[i][j][k+1], tab_in[i][j+1][k], tab_in[i][j+1][k+1], tab_in[i][j+2][k], tab_in[i][j+2][k+1])
                    tab_out[i][line][colomn] = tmp
                elif j == 10 and k!=10:
                    tmp = max(tab_in[i][j][k], tab_in[i][j][k+1], tab_in[i][j][k+2], tab_in[i][j+1][k], tab_in[i][j+1][k+1], tab_in[i][j+1][k+2])
                    tab_out[i][line][colomn] = tmp
                elif k == 10 and j == 10:
                    tmp = max(tab_in[i][j][k], tab_in[i][j][k+1], tab_in[i][j+1][k], tab_in[i][j+1][k+1])
                    tab_out[i][line][colomn] = tmp
                colomn += 1
            line += 1
        for L in range(8):
            tab_out[i][7][L] = 0.0
    return tab_out
def maxpool_3(tab_in):
    tab_out=[[[0 for i in range(3)] for j in range(3)] for k in range(20)]
    for i in range(20):
        line = 0
        for j in range(0, 6, 2):
            colomn = 0
            for k in range(0, 6, 2):
                tmp = 0
                if k < 4 and j < 4:
                    tmp = max(tab_in[i][j][k], tab_in[i][j][k+1], tab_in[i][j][k+2], tab_in[i][j+1][k], tab_in[i][j+1][k+1], tab_in[i][j+1][k+2], tab_in[i][j+2][k], tab_in[i][j+2][k+1], tab_in[i][j+2][k+2])
                    tab_out[i][line][colomn] = tmp
                elif k == 4 and j<4:
                    tmp = max(tab_in[i][j][k], tab_in[i][j][k+1], tab_in[i][j+1][k], tab_in[i][j+1][k+1], tab_in[i][j+2][k], tab_in[i][j+2][k+1])
                    tab_out[i][line][colomn] = tmp
                elif j == 4 and k<4:
                    tmp = max(tab_in[i][j][k], tab_in[i][j][k+1], tab_in[i][j][k+2], tab_in[i][j+1][k], tab_in[i][j+1][k+1], tab_in[i][j+1][k+2])
                    tab_out[i][line][colomn] = tmp
                elif k == 4 and j == 4:
                    tmp = max(tab_in[i][j][k], tab_in[i][j][k+1], tab_in[i][j+1][k], tab_in[i][j+1][k+1])
                    tab_out[i][line][colomn] = tmp
                colomn += 1
            line += 1
    return tab_out
        