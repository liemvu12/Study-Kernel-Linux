// SPDX-License-Identifier: GPL-2.0
/*
 * Generic platform driver skeleton with Device Tree support
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/err.h>
#include <linux/slab.h>

/* --- 1. Cấu trúc dữ liệu thiết bị --- */
struct my_driver_data {
	struct device *dev;
	struct gpio_desc *some_gpio;
	// Thêm các tài nguyên khác: clk, irq, regmap, ...
};

/* --- 2. Hàm xử lý chính khi probe thiết bị --- */
static int my_driver_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct my_driver_data *drvdata;
	struct gpio_desc *gpio;
	int ret = 0;

	dev_info(dev, "Probe start\n");

	drvdata = devm_kzalloc(dev, sizeof(*drvdata), GFP_KERNEL);
	if (!drvdata)
		return -ENOMEM;

	drvdata->dev = dev;

	/* --- 3. Đọc GPIO từ DT --- */
	gpio = devm_gpiod_get(dev, "mygpio", GPIOD_OUT_LOW);
	if (IS_ERR(gpio)) {
		dev_err(dev, "Failed to get GPIO\n");
		return PTR_ERR(gpio);
	}
	drvdata->some_gpio = gpio;

	/* --- 4. Thiết lập ban đầu, đăng ký thiết bị phụ nếu cần --- */
	gpiod_set_value(drvdata->some_gpio, 1);  // Ví dụ: bật GPIO

	platform_set_drvdata(pdev, drvdata);

	dev_info(dev, "Probe done\n");
	return 0;
}

/* --- 5. Hàm shutdown hoặc remove (tuỳ chọn) --- */
static void my_driver_shutdown(struct platform_device *pdev)
{
	struct my_driver_data *drvdata = platform_get_drvdata(pdev);
	dev_info(&pdev->dev, "Shutdown\n");

	if (drvdata->some_gpio)
		gpiod_set_value(drvdata->some_gpio, 0);  // Ví dụ: tắt GPIO
}

static int my_driver_remove(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "Remove\n");
	return 0;
}

/* --- 6. Bảng match với Device Tree --- */
static const struct of_device_id my_driver_of_match[] = {
	{ .compatible = "vendor,my-device", },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, my_driver_of_match);

/* --- 7. Định nghĩa platform_driver --- */
static struct platform_driver my_driver = {
	.probe    = my_driver_probe,
	.remove   = my_driver_remove,      // nếu cần
	.shutdown = my_driver_shutdown,    // nếu cần
	.driver   = {
		.name           = "my_driver",
		.of_match_table = my_driver_of_match,
	},
};

/* --- 8. Đăng ký module --- */
module_platform_driver(my_driver);

MODULE_AUTHOR("Your Name <your.email@example.com>");
MODULE_DESCRIPTION("Generic Platform Driver Skeleton with DT support");
MODULE_LICENSE("GPL");
