
#[derive(Clone)]

pub struct StringAdjustment {
    string_number: i32,
    step: i32
}

impl StringAdjustment {
    pub fn new(string_number: i32, step: i32) -> Self {
        StringAdjustment {
            string_number,
            step
        }
    }

    pub fn string_number(&self) -> i32 {
        self.string_number
    }
    pub fn step(&self) -> i32 {
        self.step
    }

    pub fn description(&self) -> String {
        format!("string_number: {}, step: {}", self.string_number, self.step)
    }
}

#[cfg(test)]
mod tests {
    use crate::string_adjustment::StringAdjustment;

    #[test]
    fn test_new_string_adjustment() {
        let string_adjustment = StringAdjustment::new(1, 2);
        assert_eq!(string_adjustment.string_number, 1);
        assert_eq!(string_adjustment.step, 2);
        assert!(!string_adjustment.description().is_empty())
    }
}