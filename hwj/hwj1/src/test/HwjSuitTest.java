package test;

import org.junit.jupiter.api.Nested;

/*
    Workaround for SuitTest Class (JUnit5 + IntelliJ 2017.)
    > https://stackoverflow.com/questions/39085905/junit-5-empty-test-suite-in-intellij-idea-when-using-junit-jupiter-engine
 */

public class HwjSuitTest {

    @Nested
    public class test1 extends TestHwj1 {}

    @Nested
    public class test2 extends TestHwj3 {}

    @Nested
    public class test3 extends TestHwj4 {}
}
