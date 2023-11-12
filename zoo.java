package output;

public class zoo {
    public static void main(String[] arg){
        Person person = new Person();
        person.setName("老王");
        person.setAge("30");
        Dog dog = new Dog();
        dog.lookHome();
        dog.setName("张佳浩");
        dog.setColor("黑颜色");
        dog.setAge("2");
        String something = "骨头";
        person. keepPet(dog,something);
        System.out.println(" ");
        person.setAge("25");
        Cat cat = new Cat();
        cat.catchMouse();
        cat.setName("王俊淇");
        cat.setColor("灰颜色");
        cat.setAge("3");
        something = "鱼";
        person. keepPet(cat,something);
    }


}
class Animal {
    String name;
    String age;
    String color;

    void setName(String name) {
        this.name = name;
    }

    String getName(String name) {
        return this.name;
    }

    void setAge(String age) {
        this.age = age;
    }

    String getAge(String age) {
        return this.age;
    }

    void setColor(String color) {
        this.color = color;
    }

    String getColor() {
        return this.color;
    }
}
class Dog extends Animal{
    void eat(String something){
        System.out.println("dog"+" "+"eating" +something);
    }
    void lookHome(){
        System.out.println("狗看家");
    }
}
class Cat extends Animal{
    void eat(String something){
        System.out.println("cat"+" "+"eating" +something);
    }
    void catchMouse(){
        System.out.println("猫逮老鼠");
    }
}

class Person{
    String name;
    String age;
    void setName(String name){
        this.name = name;
    }

    void setAge(String age){
        this.age = age;
    }
    String getName(String name){
        return this.name;
    }
    String getAge(String age){
        return this.age;
    }
    void keepPet(Dog dog,String something){
        System.out.print("年龄为"+age+"岁"+"的"+name+"养了一只"+dog.color+"的"+dog.age+"岁的"+"狗"+dog.name);
        System.out.println(" ");
        System.out.print(dog.age+"岁"+"的"+dog.color+"的");
        System.out.print("狗"+dog.name+"两只前腿死死的抱住"+something+"猛吃");
    }
    void keepPet(Cat cat,String something){
        System.out.print("年龄为"+age+"岁的"+name+"养了一只"+cat.color+"的"+cat.age+"岁的"+"猫"+cat.name);
        System.out.println(" ");
        System.out.print(cat.age+"岁的"+cat.color+"的");
        System.out.print("猫"+cat.name+"眯着眼睛侧着头吃"+something);
    }
}













