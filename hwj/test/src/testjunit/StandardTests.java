package testjunit;

import org.junit.jupiter.api.*;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.fail;

public class StandardTests {
    @BeforeAll
    static void initAll() {
        System.out.println("Start: Before All Tests");
    }

    @BeforeEach
    void init() {
        System.out.println("Before Each Test");
    }

    @Test
    void succeedingTest() {
        assertEquals(2, 1 + 1);
    }

    @Test
    void failingTest() {
        //fail("a failing test");
    }

    @Test
    @Disabled("for demonstration purposes")
    void skippedTest() {
        // not executed
    }

    @AfterEach
    void tearDown() {
        System.out.println("Stop: After Each Test");
    }

    @AfterAll
    static void tearDownAll() {
        System.out.println("Stop: After All Tests");
    }
}

