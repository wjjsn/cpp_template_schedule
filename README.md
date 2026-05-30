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
