### 描述

50行实现的时间片轮询调度器。全静态类型,无运行时开销

### 编译
安装[meson](https://mesonbuild.com/)和[ninja](https://github.com/ninja-build/ninja)

```sh
meson setup build
ninja -C build/

# 运行示例
./build/schedule
```

### 在你的项目中使用

在subproject中添加`template_schedule.wrap`

```ini
[wrap-git]
url = https://github.com/wjjsn/cpp_template_schedule.git
revision = HEAD

[provide]
dependency_names = template_schedule
```