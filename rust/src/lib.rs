mod note;
mod note_value;
mod note_names;
mod scale;
mod chord;
mod guitar_string;
mod string_adjustment;
mod guitar_adjustment;

pub fn add(left: u64, right: u64) -> u64 {
    left + right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }
}
