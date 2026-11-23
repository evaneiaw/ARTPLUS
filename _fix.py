path = r'src/color_management/color_lib_info.h'
text = open(path, 'r', encoding='utf-8').read()
old = '    QString colorName() const;`n    ColorType colorSpaceType() const;'
new = '    QString colorName() const;\n    ColorType colorSpaceType() const;'
assert old in text
open(path, 'w', encoding='utf-8', newline='\n').write(text.replace(old, new))
print('ok')
