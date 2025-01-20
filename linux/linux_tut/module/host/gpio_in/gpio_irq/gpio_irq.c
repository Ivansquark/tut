#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/module.h>

// Meta information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Me");
MODULE_DESCRIPTION("Test chardev module interface");

#define BUT1 60 // EMIO GPIO number

unsigned int irq_number;

static irqreturn_t gpio_irq_handler(int irq, void* dev_id) {
    printk(KERN_INFO "Gpio was triggered\n");
    return IRQ_HANDLED;
}

static int __init gpio_irq_init(void) {
    printk(KERN_INFO "gpio irq init\n");

    if (!gpio_is_valid(BUT1)) {
            pr_err("Invalid GPIO\n");
            return -ENODEV;
        }
    // request gpio
    if (gpio_request(BUT1, "gpio-60")) {
        pr_err("Invalid GPIO\n");
        return -ENODEV;
    }
    // Set GPIO as output and initial value to 0
    if (gpio_direction_input(BUT1)) {
        gpio_free(BUT1);
        return -EPERM;
    }

    irq_number = gpio_to_irq(BUT1);

    if (request_irq(irq_number, gpio_irq_handler, IRQF_TRIGGER_RISING,
                    "my_but1_irq", NULL) != 0) {
        ///
        printk("Error!\nCan not request interrupt nr.: %d\n", irq_number);
        gpio_free(BUT1);
        return -EPERM;
    }

    return 0;
}
static void __exit gpio_irq_exit(void) {
    gpio_free(BUT1);
    printk(KERN_INFO "Char_dev exit\n");
}

module_init(gpio_irq_init);
module_exit(gpio_irq_exit);
