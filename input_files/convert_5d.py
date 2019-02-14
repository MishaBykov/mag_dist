if __name__ == '__main__':
    file_in = open("5d_temp_no_format.txt")
    file_out = open("5d_temp.txt", 'w')

    for line in file_in:
        line = line.split()
        fs = []
        max_ind = 0
        for field in line:
            field = field.replace('[', '')
            field = field.replace(']', '')
            field = field.split(',')
            field = list(map(lambda x: int(x), field))
            fs.append([0 for i in range(0, max_ind + 1)])
            for j in field:
                if j > max_ind:
                    max_ind = j
                    for f in fs:
                        while max_ind >= len(f):
                            f.append(0)
                fs[-1][j] = 1
        for f in fs:
            for i in f:
                file_out.write(str(i))
            file_out.write('\n')
        file_out.write('\n')
    file_in.close()
    file_out.close()
