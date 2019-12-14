#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys
import json

if len(sys.argv) != 2:
    sys.stderr.write('Please indicate the path of Res.json.\n')
    sys.exit(1)

def main():
    res_out = sys.stdout
    res_dict_filename = sys.argv[1]
    res_dict = json.loads(open(res_dict_filename, 'r').read())

    res_lengths = {}

    for key, res in sorted(res_dict.items()):
        res_id = int(key, 10)
        res_file = res['file']
        res_path = os.path.join(os.path.dirname(res_dict_filename), res_file)

        res_out.write('static const unsigned char res_%d[] = {' % (res_id))
        res_length = 0
        with open(res_path, 'rb') as res_in:
            while True:
                buf = res_in.read(8192)
                if not buf:
                    break
                res_length += len(buf)
                if sys.version_info[0] < 3:
                    for byte in buf:
                        res_out.write('%d,' % (ord(byte)))
                else:
                    for byte in buf:
                        res_out.write('%d,' % (byte))
        res_out.write('};\n')
        res_lengths[res_id] = res_length

    res_out.write('struct Resource\n{\n'
                  '\t' 'unsigned int id;' '\n'
                  '\t' 'unsigned int type;' '\n'
                  '\t' 'const unsigned char *data;' '\n'
                  '\t' 'unsigned int size;' '\n'
                  '};\n')

    res_out.write('extern const Resource RES[] =\n{\n')
    for key, res in sorted(res_dict.items()):
        res_id = int(key, 10)
        res_type = res['type']
        res_file = res['file']
        res_length = res_lengths[res_id]

        while len(res_type) < 4:
            res_type += ' '
        if len(res_type) != 4:
            raise ValueError('invalid resource type')

        res_out.write("\t{%d, '%s', res_%d, %d}, /* %s */\n" % \
                      (res_id, res_type, res_id, res_length, res_file))
    res_out.write('};\n')
    res_out.write('extern const unsigned int NRES = %d;\n' % (len(res_dict)))

if __name__ == '__main__':
    main()
