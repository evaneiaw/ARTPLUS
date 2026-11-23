path = r'src/color_management/color_lib_info.cpp'
text = open(path, "r", encoding="utf-8").read()
old = 'QString ColorLibInfo::colorName() const { return m_colorName; }`nColorType ColorLibInfo::colorSpaceType() const { return m_colorSpaceType; }'
new = 'QString ColorLibInfo::colorName() const { return m_colorName; }\nColorType ColorLibInfo::colorSpaceType() const { return m_colorSpaceType; }'
assert old in text
open(path, "w", encoding="utf-8", newline="\n").write(text.replace(old, new))
print("ok")
