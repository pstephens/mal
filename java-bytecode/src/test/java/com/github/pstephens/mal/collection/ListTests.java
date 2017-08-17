package com.github.pstephens.mal.collection;

import org.junit.Test;

import static org.junit.Assert.*;

public class ListTests {
    @Test
    public void toString_should_emit_for_empty_list() {
        List<Integer> list = List.empty();

        String str = list.toString();

        assertEquals("()", str);
    }

    @Test
    public void toString_should_emit_for_two_item_list() {
        List<Integer> list = List.create(12, 13);

        String str = list.toString();

        assertEquals("(12, 13)", str);
    }

    @Test
    public void toString_should_emit_for_nested_lists() {
        List<Object> list =
                List.create(
                        List.create("5", "A"),
                        List.create(1, 5));

        String str = list.toString();

        assertEquals("((5, A), (1, 5))", str);
    }

    @Test
    public void isEmpty_should_return_true_for_empty_list() {
        List<Integer> list = List.empty();

        assertTrue(list.isEmpty());
    }

    @Test
    public void isEmpty_should_return_false_for_single_item_list() {
        List<Double> list = List.create(5.0);

        assertFalse(list.isEmpty());
    }

    @Test
    public void isEmpty_should_return_true_for_tail_of_single_item_list() {
        List<Float> list = List.create(3.14F);

        List<Float> tail = list.tail();

        assertTrue(tail.isEmpty());
    }

    @Test(expected = UnsupportedOperationException.class)
    public void head_should_fail_on_empty_list() {
        List<Boolean> list = List.empty();

        list.head();
    }

    @Test
    public void head_should_return_head_value_on_list_with_values() {
        List<Integer> list = List.create(55, 5, 9, 10, 22);

        int head = list.head();

        assertEquals(55, head);
    }

    @Test(expected = UnsupportedOperationException.class)
    public void tail_should_fail_on_empty_list() {
        List<Short> list = List.empty();

        list.tail();
    }

    @Test
    public void tail_should_return_tail_list_on_list_with_values() {
        List<String> list = List.create("A", "B", "C");

        List<String> tail = list.tail();

        assertEquals(List.create("B", "C"), tail);
    }

    @Test
    public void reverse_on_empty_should_return_empty() {
        List<List> list = List.empty();

        List<List> reversed = list.reverse();

        assertEquals(List.empty(), reversed);
    }

    @Test
    public void reverse_on_number_list_should_return_reversed_sequence() {
        List<Integer> list = List.create(3, 1, 4, 1, 5);

        List<Integer> reversed = list.reverse();

        assertEquals(List.create(5, 1, 4, 1, 3), reversed);
    }

    @Test
    public void equals_should_return_value_according_to_equality() {
        assertTrue(List.empty().equals(List.empty()));
        assertFalse(List.empty().equals(List.create(1)));
        assertFalse(List.create(1).equals(List.empty()));
        assertFalse(List.empty().equals(null));
        assertFalse(List.empty().equals("Random"));
        assertTrue(List.create(5).equals(List.create(5)));
        assertFalse(List.create(null, 5).equals(List.create(null, 6)));
        assertFalse(List.create(null).equals(List.create(5)));
    }

    @Test
    public void hashCode_should_operate_on_empty_list() {
        int h1 = List.empty().hashCode();
        int h2 = List.empty().hashCode();

        assertEquals(h1, h2);
    }

    @Test
    public void hashCode_should_return_diff_code_for_two_lists_with_null_but_diff_size() {
        int h1 = List.create(null).hashCode();
        int h2 = List.create(null, null).hashCode();

        assertNotEquals(h1, h2);
    }

    @Test
    public void hashCode_should_return_same_for_same_4_element_list_values() {
        int h1 = List.create("A", "B", "C").hashCode();
        int h2 = List.create("A", "B", "C").hashCode();

        assertEquals(h1, h2);
    }
}
