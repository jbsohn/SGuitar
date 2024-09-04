use crate::string_adjustment::StringAdjustment;

pub struct GuitarAdjustment {
    adjustment_id: String,
    adjustments: Vec<StringAdjustment>,
}

impl GuitarAdjustment {
    pub fn new(adjustment_id: String) -> Self {
        GuitarAdjustment {
            adjustment_id,
            adjustments: vec![],
        }
    }

    pub fn get_adjustment_id(&self) -> String {
        self.adjustment_id.clone()
    }

    pub fn clear_adjustments(&mut self) {
        self.adjustments.clear()
    }

    pub fn add_string_adjustment(&mut self, string_adjustment: StringAdjustment) {
        self.adjustments.push(string_adjustment);
    }

    pub fn get_string_adjustments(&self) -> Vec<StringAdjustment> {
        self.adjustments.clone()
    }

    pub fn string_adjustment_for_string_number(&self, string_number: i32) -> Option<StringAdjustment> {
        for adjustment in &self.adjustments.clone() {
            if adjustment.get_string_number() == string_number {
                return Some(adjustment.clone());
            }
        }
        None
    }

    pub fn description(&self) -> String {
        let mut description = format!("adjustment_id: {}\n", self.adjustment_id);
        for adjustment in &self.adjustments.clone() {
            description = format!("{}{}\n", description, adjustment.description());
        }
        description
    }
}

#[cfg(test)]
mod tests {
    use crate::guitar_adjustment::GuitarAdjustment;
    use crate::string_adjustment::StringAdjustment;

    #[test]
    fn test_new_guitar_adjustment() {
        let mut guitar_adjustment = GuitarAdjustment::new(String::from("LKL"));
        guitar_adjustment.add_string_adjustment(StringAdjustment::new(1, 1));
        assert_eq!(guitar_adjustment.get_adjustment_id(), "LKL")
    }
}
